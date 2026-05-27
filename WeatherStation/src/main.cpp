#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>
#include "sensor.h"

#define WIRE_BUS_PIN 2
#define HUM_SENS_PIN 4


OneWire wire_bus(WIRE_BUS_PIN);

TempSensor temp_sens(&wire_bus);
HumSensor hum_sens(HUM_SENS_PIN,DHT11);

void setup() {
  Serial.begin(9600);
  temp_sens.begin();
  hum_sens.begin();
}

void loop() {
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
  delay(2000);
  
}
