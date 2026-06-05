#include <Arduino.h>
#include <OneWire.h>
#include <DHT.h>
#include "sensor.h"
#include "display.h"

#define WIRE_BUS_PIN 2
#define HUM_SENS_PIN 4
#define BUTTON_PIN 7
#define SCREEN_UPDATE_TIME_MS 750


OneWire wire_bus(WIRE_BUS_PIN);

TempSensor temp_sens(&wire_bus);
HumSensor hum_sens(HUM_SENS_PIN,DHT11);
Display lcd = Display(0x27,16,2);
unsigned long last_update = millis();

void setup() {
    Serial.begin(9600);
    // use internal pullup resistor to avoid floating voltages
    pinMode(BUTTON_PIN,INPUT_PULLUP);
    lcd.begin();
    temp_sens.begin();
    hum_sens.begin();
    lcd.printReadings(temp_sens,hum_sens);
    delay(2000);
}

void loop() {
    // sensors and button update do their own thing, no need to slow them down by design
    temp_sens.updateReading();
    hum_sens.updateReading();
    // invert the logic (since we're working with a pullup resistor)
    lcd.togglePrintMode(!digitalRead(BUTTON_PIN));

    if (millis() - last_update >= SCREEN_UPDATE_TIME_MS)
    {
      lcd.printReadings(temp_sens,hum_sens);
      last_update = millis();
    }
}
