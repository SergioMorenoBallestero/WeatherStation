#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "sensor.h"

OneWire wire(2);
Sensor sens = Sensor(&wire);

void setup() {
  Serial.begin(9600);
  sens.sensor.begin();
}

void loop() {
  sens.updateReading();
  Serial.print("Reading: ");
  Serial.print(sens.getReading());
  Serial.print(" ºC\n");
  delay(2000);
}
