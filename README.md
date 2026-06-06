# WeatherStation
WeatherStation is a basic Arduino project featuring the Arduino Nano development board as well as the DHT11 humidity/temperature sensor and DS18B20 sensor. It shows, depending on the choice of the user, the current reading and the min/max readings of either humidity (%) or temperature (C).

# Hardware requirements
* ATmega328p  Arduino Nano development board
* DS18B20 OneWire temperature sensor
* DHT11 humidity/temperature sensor
* LCD module with an I2C backpack
* 4-leg button

# Software requirements and dependencies
* VS Code IDE with the PlatformIO extension installed
* Library dependencies: milesburton/DallasTemperature@^4.0.6, paulstoffregen/OneWire@^2.3.8, adafruit/DHT sensor library@^1.4.7, blackhack/LCD_I2C@^2.4.0

# How to build
* Wiring part:
  * DHT11:
    * Data: D4
    * VCC: 3.3V
    * GND: GND
  * DS18B20:
    * Data: D2
    * VCC: 3.3V
    * GND: GND
  * LCD_I2C module:
    * SDA: A4
    * SDL: A5
    * VCC: 5V
    * GND: GND
  * 4-leg button:
    * Data: D7
    * GND: GND
* From the PlatformIO menu, clone the repository
* With the circuit correctly wired, plug the board to a USB port and click 'Upload' on the PlatformIO menu.

# Basic functioning
Upon startup, the LCD will display a welcome message for 2 seconds. Then, it will jump to the displaying of temperature readings. Pressing and releasing the button once will change the display mode to show humidity readings. Pressing and releasing the button again will change the display mode to show temperature readings again. If the system gets locked up, press the reset button in the Arduino Nano development board to reboot the program.
