## Connections

### NodeMCU ESP8266 to LCD 1

- D2 (GPIO4) → SDA
- D1 (GPIO5) → SCL
- 3.3V → VCC
- GND → GND
- I2C Address → 0x27

### NodeMCU ESP8266 to LCD 2

- D2 (GPIO4) → SDA
- D1 (GPIO5) → SCL
- 3.3V → VCC
- GND → GND
- I2C Address → 0x26

Both LCDs share the same I2C SDA and SCL lines but use different I2C addresses.
