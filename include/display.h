#ifndef DISPLAY_H
#define DISPLAY_H

#include <LCD_I2C.h>

#include "sensor.h"

#define UPWARDS_ARROW 0
#define DOWNWARDS_ARROW 1

enum class PrintMode 
{
    WELCOME,
    TEMPERATURE,
    HUMIDITY
};

enum class ButtonState
{
    UNPRESSED,
    PRESSED,
    RELEASED
};

class Display
{
    private:
        LCD_I2C hw;
        PrintMode print_mode;
        ButtonState button_state;
    public:
        Display(uint8_t address, uint8_t cols, uint8_t rows);
        ~Display() = default;
        void begin();
        void printReadings(TempSensor& temp_sensor, HumSensor& hum_sensor);
        void togglePrintMode(bool button_pressed);
};

#endif