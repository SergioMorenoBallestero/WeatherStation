#ifndef SENSOR_H
#define SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>

class Sensor
/*A sensor will give a reading which we will check. We make use of some kind of timer to add
a new reading to the array*/
{
    private:
        double current_reading;
        double readings[10];
        int readings_performed;
    public:
        DallasTemperature sensor; // 100% a better way to do this exists
        Sensor(OneWire* wire);
        ~Sensor() = default;
        double getReading() const;
        void updateReading();
        void addToReadings();
        double computeAverage();
};

#endif