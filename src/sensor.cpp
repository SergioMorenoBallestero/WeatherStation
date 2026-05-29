#include "sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

// constructors
Sensor::Sensor()
 : current_reading{}, readings{}, readings_performed{}
{}

TempSensor::TempSensor(OneWire* wire_bus) : Sensor(), hw{wire_bus}
{}

HumSensor::HumSensor(uint8_t pin, uint8_t model) : Sensor(), hw{pin,model}
{}

// base class methods
float Sensor::getReading() const
{return current_reading;}

// this function is supposed to be called when the reading has updated
void Sensor::addToReadings()
{
    readings[readings_performed % READING_ARRAY_SIZE] = current_reading;
    ++readings_performed;
}

float Sensor::computeAverage()
{
    float sum{};
    for (float reading : readings)
        sum += reading;
    return sum / READING_ARRAY_SIZE;
}

void Sensor::printReadings()
{
    Serial.println("Last 10 measurements:");
    Serial.print("{");
    for (size_t i = 0; i < READING_ARRAY_SIZE; ++i)
    {
        Serial.print(readings[i]);
        if (i == READING_ARRAY_SIZE - 1)
            Serial.print("}");
        else
            Serial.print(",");
    }
}

// hardware-specific methods
void TempSensor::begin()
{hw.begin();}

void TempSensor::updateReading()
{
    hw.requestTemperatures();
    float temp = hw.getTempCByIndex(0);
    if (temp == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Error: device disconnected");
        return;
    }
    current_reading = temp;
    addToReadings();
        
}

void HumSensor::begin()
{hw.begin();}

void HumSensor::updateReading()
{
    float reading = hw.readHumidity();
    if (reading < 0 || reading > 100) 
    {
            Serial.println("Error: the reading was invalid");
            return;
    }
    current_reading = reading;
    addToReadings();
}