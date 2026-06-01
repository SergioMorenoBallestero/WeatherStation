#ifndef DISPLAY_H
#define DISPLAY_H

#include <LCD_I2C.h>

#include "sensor.h"

enum class Mode 
{
    welcome,
    temperature,
    humidity
};


class Display
{
    private:
        LCD_I2C hw;
        Mode print_mode;
    public:
        Display(uint8_t address, uint8_t cols, uint8_t rows);
        ~Display() = default;
        void begin();
        void printReadings(TempSensor& temp_sensor, HumSensor& hum_sensor);
        void togglePrintMode(bool button_pressed);
};

#endif