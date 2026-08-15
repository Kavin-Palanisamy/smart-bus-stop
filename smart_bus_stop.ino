#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

/* ================= WIFI + FIREBASE ================= */
#define WIFI_SSID     "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define DATABASE_URL  "YOUR_FIREBASE_DATABASE_URL"
#define DATABASE_SECRET "YOUR_FIREBASE_DATABASE_SECRET"
/* ================= FIREBASE ================= */
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

/* ================= LCD ================= */
LiquidCrystal_I2C lcd1(0x27,16,2);
LiquidCrystal_I2C lcd2(0x26,16,2);

/* ================= BUS DATA ================= */
String buses[] = {"bus_23","bus_45","bus_78","bus_115"};
const int totalBuses = 4;

#define MAX_UPCOMING 4

/* ================= STRUCTS ================= */
struct ScrollState{
  String line1;
  String line2;
  int index = 0;
  unsigned long lastMove = 0;
};

struct BusInfo{
  String line1;
  String line2;
};

/* ================= GLOBALS ================= */
ScrollState s1, s2;
ScrollState up1, up2;

BusInfo upcoming1[MAX_UPCOMING];
BusInfo upcoming2[MAX_UPCOMING];

int upcomingCount1 = 0;
int upcomingCount2 = 0;

bool showUpcoming = false;
int upcomingIndex = 0;
unsigned long modeTimer = 0;

/* ================= TIME HELPERS ================= */
int timeToMin(String t){
  return t.substring(0,2).toInt()*60 +
         t.substring(3,5).toInt();
}

String minToTime(int m){
  m = (m + 1440) % 1440;

  char buf[6];
  sprintf(buf,"%02d:%02d",m/60,m%60);

  return String(buf);
}

/* ================= 12 HR FORMAT ================= */
String to12Hr(String time24){

  int h = time24.substring(0,2).toInt();
  int m = time24.substring(3,5).toInt();

  String ampm = (h >= 12) ? " PM" : " AM";

  h = h % 12;

  if(h == 0)
    h = 12;

  char buf[10];
  sprintf(buf,"%02d:%02d",h,m);

  return String(buf) + ampm;
}

/* ================= FETCH BUS ================= */
void fetchBus(ScrollState &s,
              String stop,
              BusInfo upcoming[],
              int &count){

  struct tm t;

  if(!getLocalTime(&t)){
    s.line1 = "Time Error     ";
    s.line2 = "Retrying...    ";
    count = 0;
    return;
  }

  int nowMin = t.tm_hour*60 + t.tm_min;

  int arr[totalBuses];
  int idx[totalBuses];

  int valid = 0;

  for(int i=0;i<totalBuses;i++){

    String base =
      "/smart_bus_stop/buses/" +
      buses[i] +
      "/stops/" +
      stop;

    if(!Firebase.RTDB.getString(&fbdo,
        base + "/time"))
      continue;

    int sched =
      timeToMin(fbdo.stringData());

    Firebase.RTDB.getInt(&fbdo,
      base + "/delay");

    int delay = fbdo.intData();

    int arrival = sched + delay;

    if(arrival >= nowMin){

      arr[valid] = arrival;
      idx[valid] = i;

      valid++;
    }
  }

  if(valid == 0){

    s.line1 = "No Bus Avail   ";
    s.line2 = "Please Wait    ";

    count = 0;
    return;
  }

  /* ===== SORT ===== */
  for(int i=0;i<valid-1;i++){

    for(int j=i+1;j<valid;j++){

      if(arr[j] < arr[i]){

        int ta = arr[i];
        arr[i] = arr[j];
        arr[j] = ta;

        int ti = idx[i];
        idx[i] = idx[j];
        idx[j] = ti;
      }
    }
  }

  /* ===== CURRENT BUS ===== */
  String bus = buses[idx[0]];

  Firebase.RTDB.getString(&fbdo,
    "/smart_bus_stop/buses/" +
    bus +
    "/route");

  String route = fbdo.stringData();

  Firebase.RTDB.getString(&fbdo,
    "/smart_bus_stop/buses/" +
    bus +
    "/stops/" +
    stop +
    "/time");

  String sched = fbdo.stringData();

  Firebase.RTDB.getInt(&fbdo,
    "/smart_bus_stop/buses/" +
    bus +
    "/stops/" +
    stop +
    "/delay");

  int delay = fbdo.intData();

  String sched12 = to12Hr(sched);

  String final24 =
    minToTime(
      timeToMin(sched) + delay
    );

  String final12 = to12Hr(final24);

  s.line1 =
    "Bus " +
    bus.substring(4) +
    " " +
    route +
    " " +
    sched12 +
    "   ";

  if(delay == 0){

    s.line2 = "On Time        ";

  }else{

    s.line2 =
      "Delay +" +
      String(delay) +
      " min " +
      final12 +
      "   ";
  }

  s.index = 0;

  /* ===== UPCOMING ===== */
  count = min(MAX_UPCOMING, valid-1);

  for(int i=0;i<count;i++){

    String b = buses[idx[i+1]];

    Firebase.RTDB.getString(&fbdo,
      "/smart_bus_stop/buses/" +
      b +
      "/route");

    String r = fbdo.stringData();

    Firebase.RTDB.getString(&fbdo,
      "/smart_bus_stop/buses/" +
      b +
      "/stops/" +
      stop +
      "/time");

    String t1 = fbdo.stringData();

    upcoming[i].line1 =
      "Next Bus " +
      b.substring(4) +
      " " +
      r +
      " " +
      to12Hr(t1) +
      "   ";

    upcoming[i].line2 =
      "Upcoming       ";
  }
}

/* ================= SCROLL ================= */
void runScroll(LiquidCrystal_I2C &lcd,
               ScrollState &s){

  bool staticLine2 =
    s.line2.startsWith("On Time") ||
    s.line2.startsWith("Upcoming");

  /* ===== SLOW SPEED ===== */
  if(millis() - s.lastMove < 700)
    return;

  s.lastMove = millis();

  lcd.setCursor(0,0);

  lcd.print(
    s.line1.substring(
      s.index,
      s.index + 16
    )
  );

  lcd.setCursor(0,1);

  if(staticLine2){

    lcd.print(
      s.line2.substring(0,16)
    );

  }else{

    lcd.print(
      s.line2.substring(
        s.index,
        s.index + 16
      )
    );
  }

  s.index++;

  if(s.index >
     s.line1.length() - 16){

    s.index = 0;
  }
}

/* ================= SETUP ================= */
void setup(){

  Serial.begin(115200);

  Wire.begin(D2,D1);

  lcd1.init();
  lcd1.backlight();

  lcd2.init();
  lcd2.backlight();

  lcd1.print("Connecting...");
  lcd2.print("Connecting...");

  /* ===== WIFI ===== */
  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  while(WiFi.status()!=WL_CONNECTED)
    delay(300);

  lcd1.clear();
  lcd2.clear();

  lcd1.print("WiFi Connected");
  lcd2.print("WiFi Connected");

  delay(1000);

  /* ===== FIREBASE ===== */
  config.database_url = DATABASE_URL;

  config.signer.tokens.legacy_token =
    DATABASE_SECRET;

  Firebase.begin(&config,&auth);

  lcd1.clear();
  lcd2.clear();

  lcd1.print("Firebase OK");
  lcd2.print("Firebase OK");

  delay(1000);

  /* ===== TIME ===== */
  configTime(
    19800,
    0,
    "in.pool.ntp.org",
    "time.google.com"
  );

  while(!time(nullptr))
    delay(300);

  /* ===== INITIAL FETCH ===== */
  fetchBus(
    s1,
    "stop1",
    upcoming1,
    upcomingCount1
  );

  fetchBus(
    s2,
    "stop2",
    upcoming2,
    upcomingCount2
  );
}

/* ================= LOOP ================= */
void loop(){

  unsigned long now = millis();

  /* ===== UPCOMING MODE ===== */
  if(now - modeTimer >
     (showUpcoming ? 10000 : 60000)){

    modeTimer = now;

    if(showUpcoming){

      upcomingIndex++;

      if(upcomingIndex >= upcomingCount1){

        showUpcoming = false;
        upcomingIndex = 0;
      }

    }else{

      showUpcoming = true;
      upcomingIndex = 0;
    }

    if(showUpcoming &&
       upcomingCount1 > 0){

      up1.line1 =
        upcoming1[upcomingIndex].line1;

      up1.line2 =
        upcoming1[upcomingIndex].line2;

      up1.index = 0;

      up2.line1 =
        upcoming2[upcomingIndex].line1;

      up2.line2 =
        upcoming2[upcomingIndex].line2;

      up2.index = 0;
    }
  }

  /* ===== DISPLAY ===== */
  if(showUpcoming &&
     upcomingCount1 > 0){

    runScroll(lcd1, up1);

  }else{

    runScroll(lcd1, s1);
  }

  if(showUpcoming &&
     upcomingCount2 > 0){

    runScroll(lcd2, up2);

  }else{

    runScroll(lcd2, s2);
  }

  /* ===== REFRESH EVERY 1 MIN ===== */
  static unsigned long refresh = 0;

  if(now - refresh > 60000){

    fetchBus(
      s1,
      "stop1",
      upcoming1,
      upcomingCount1
    );

    fetchBus(
      s2,
      "stop2",
      upcoming2,
      upcomingCount2
    );

    refresh = now;
  }
}
