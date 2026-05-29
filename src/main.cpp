#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include <LCD_I2C.h>
#include "sensor.h"

#define WIRE_BUS_PIN 2
#define HUM_SENS_PIN 4


OneWire wire_bus(WIRE_BUS_PIN);

TempSensor temp_sens(&wire_bus);
HumSensor hum_sens(HUM_SENS_PIN,DHT11);
LCD_I2C lcd = LCD_I2C(0x27,16,2);


void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("Good morning!!");
  temp_sens.begin();
  hum_sens.begin();
}

void loop() {
  delay(2000);
  lcd.clear();
  lcd.print("I got to the loop! :D");
  temp_sens.updateReading();
  hum_sens.updateReading();
  Serial.print("Temp reading: ");
  Serial.print(temp_sens.getReading());
  Serial.print(" ºC\n");
  temp_sens.printReadings();
  Serial.print("Humidity reading: ");
  Serial.print(hum_sens.getReading());
  Serial.print(" %\n");
  hum_sens.printReadings();
}
