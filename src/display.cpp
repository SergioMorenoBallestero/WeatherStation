#include "display.h"

Display::Display(uint8_t address, uint8_t cols, uint8_t rows)
: hw{address,cols,rows}, print_mode{PrintMode::WELCOME}, button_state{ButtonState::UNPRESSED}
{}

void Display::begin()
{
    hw.begin();
    hw.backlight();
    // prepare min/max characters
    byte upwards_arrow[8] = {B00100,B01110,B11111,B00100,B00100,B00100,B00100,B00100};
    byte downwards_arrow[8] = {B00100,B00100,B00100,B00100,B00100,B11111,B01110,B00100};
    hw.createChar(UPWARDS_ARROW,upwards_arrow);
    hw.createChar(DOWNWARDS_ARROW,downwards_arrow);

}

// this function could probably be shorter
void Display::printReadings(TempSensor& temp_sensor, HumSensor& hum_sensor)
{
    bool failed_reading = false;
    Sensor* sensor;
    hw.clear();
    switch(print_mode)
    {
    case PrintMode::WELCOME:
        hw.print("WeatherStationv1");
        hw.setCursor(0,1);
        hw.print("By S. Moreno");
        // triggers change to display temperature on the next togglePrintMode() call
        button_state = ButtonState::RELEASED;
        delay(2000);
        return;
    case PrintMode::TEMPERATURE:
        sensor = &temp_sensor;
        if (sensor->getReading() == DEVICE_DISCONNECTED_C)
        {
            hw.print("Temp error");
            failed_reading = true;
        }
        else hw.print("Temps(C):");
        break;
    case PrintMode::HUMIDITY:
        sensor = &hum_sensor;
        if (sensor->getReading() == NAN) 
        {
            hw.print("Humidity error");
            failed_reading = true;
        }
        else hw.print("Humid(%):");
        break;
    }
    if (sensor == nullptr || failed_reading) return;

    // only if the reading succeeded proceed to show the other stuff
    hw.setCursor(11,0);
    hw.print(sensor->getReading(),1);
    hw.setCursor(0,1);
    hw.write(DOWNWARDS_ARROW);
    hw.print(" ");
    hw.print(sensor->getMin(),1);
    hw.print(" ");
    hw.write(UPWARDS_ARROW);
    hw.print(" ");
    hw.print(sensor->getMax(),1);
}

void Display::togglePrintMode(bool button_input)
{
    switch(button_state)
    {
    case ButtonState::UNPRESSED:
        if (button_input)
            button_state = ButtonState::PRESSED;
        break;
    case ButtonState::PRESSED:
        if (!button_input)
            button_state = ButtonState::RELEASED;
        break;
    case ButtonState::RELEASED:
        if (print_mode == PrintMode::TEMPERATURE)
            print_mode = PrintMode::HUMIDITY;
        else
            print_mode = PrintMode::TEMPERATURE;
        button_state = ButtonState::UNPRESSED;
        break;
    }
}