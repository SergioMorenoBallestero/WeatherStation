#ifndef SENSOR_H
#define SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

#define READING_ARRAY_SIZE 10

class Sensor
/*A sensor will give a reading which we will check. We make use of some kind of timer to add
a new reading to the array*/
{
    protected:
        float current_reading;
        float readings[READING_ARRAY_SIZE];
        uint16_t readings_performed;
    public:
        Sensor();
        virtual ~Sensor() = default;
        virtual void begin() = 0;
        float getReading() const;
        virtual void updateReading() = 0;
        void addToReadings();
        float computeAverage();
        void printReadings();
};

class TempSensor : public Sensor
{
    private:
        DallasTemperature hw;
    public:
        TempSensor(OneWire* wire_bus);
        virtual ~TempSensor() = default;
        void begin() override;
        void updateReading() override;
};

class HumSensor : public Sensor
{
    private:
        DHT hw;
    public:
        HumSensor(uint8_t pin, uint8_t model);
        virtual ~HumSensor() = default;
        void begin() override;
        void updateReading() override;
};

#endif