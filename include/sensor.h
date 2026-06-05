#ifndef SENSOR_H
#define SENSOR_H

#include <OneWire.h>
#include <DallasTemperature.h>
#include <DHT.h>

class Sensor
{
    protected:
        float current_reading;
        float max_reading;
        float min_reading;
        bool first_reading;
    public:
        Sensor();
        virtual ~Sensor() = default;
        virtual void begin() = 0;
        float getReading() const;
        float getMax() const;
        float getMin() const;
        virtual void updateReading() = 0;
        void updateExtremes();
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