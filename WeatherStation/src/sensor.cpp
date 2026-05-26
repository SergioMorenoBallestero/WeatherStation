#include "sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// initialize everything to 0
Sensor::Sensor(OneWire* wire)
 : sensor(wire), current_reading{}, readings{}, readings_performed{}
{}


double Sensor::getReading() const
{return current_reading;}


void Sensor::updateReading()
{
    sensor.requestTemperatures();
    double temp = sensor.getTempCByIndex(0);
    if (temp != DEVICE_DISCONNECTED_C)
        current_reading = temp;
    else
        Serial.println("Error: device disconnected");
}


// this function is supposed to be called when the reading has updated
void Sensor::addToReadings()
{
    readings[readings_performed % 10] = current_reading;
    ++readings_performed;
}

double Sensor::computeAverage()
{
    double sum{};
    for (double reading : readings)
        sum += reading;
    return sum / 10;
}