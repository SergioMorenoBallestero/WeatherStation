#include "sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// constructors
Sensor::Sensor()
 : current_reading{}, max_reading{}, min_reading{}, first_reading{true}
{}

TempSensor::TempSensor(OneWire* wire_bus) : Sensor(), hw{wire_bus}
{}

HumSensor::HumSensor(uint8_t pin, uint8_t model) : Sensor(), hw{pin,model}
{}


// base class methods
float Sensor::getReading() const
{return current_reading;}

float Sensor::getMax() const
{return max_reading;}

float Sensor::getMin() const
{return min_reading;}

void Sensor::updateExtremes()
{
    if (first_reading)
    {
        max_reading = min_reading = current_reading;
        first_reading = false;
    }
    else if (current_reading > max_reading)
        max_reading = current_reading;
    else if (current_reading < min_reading)
        min_reading = current_reading;
}


// hardware-specific methods
void TempSensor::begin()
{hw.begin();}

void TempSensor::updateReading()
{
    hw.requestTemperatures();
    float temp = hw.getTempCByIndex(0);
    current_reading = temp;
    if (temp == DEVICE_DISCONNECTED_C)
    {
        // try to initialize the device again
        begin();
        return;
    }
    updateExtremes();
}

void HumSensor::begin()
{hw.begin();}

void HumSensor::updateReading()
{
    float humidity = hw.readHumidity();
    current_reading = humidity;
    if (isnan(humidity)) return;
    updateExtremes();
}