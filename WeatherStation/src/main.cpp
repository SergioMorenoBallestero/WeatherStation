#include <Arduino.h>
#include <OneWire.h>
#include <DHT.h>
#include "sensor.h"
#include "display.h"

#define WIRE_BUS_PIN 2
#define HUM_SENS_PIN 4


OneWire wire_bus(WIRE_BUS_PIN);

TempSensor temp_sens(&wire_bus);
HumSensor hum_sens(HUM_SENS_PIN,DHT11);
Display lcd = Display(0x27,16,2);


void setup() {
  Serial.begin(9600);
  lcd.begin();
  temp_sens.begin();
  hum_sens.begin();
}

void loop() {
  // get new readings
  temp_sens.updateReading();
  hum_sens.updateReading();

  lcd.printReadings(temp_sens,hum_sens);
  lcd.togglePrintMode(true);
  delay(2000);
}
