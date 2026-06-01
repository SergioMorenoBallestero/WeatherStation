#include "display.h"

Display::Display(uint8_t address, uint8_t cols, uint8_t rows)
: hw{address,cols,rows}, print_mode{Mode::welcome}
{}

void Display::begin()
{
    hw.begin();
    hw.backlight();
}

void Display::printReadings(TempSensor& temp_sensor, HumSensor& hum_sensor)
{
    Sensor* sensor;
    hw.clear();
    switch(print_mode)
    {
    case Mode::welcome:
        hw.print("WeatherStationv1");
        hw.setCursor(0,1);
        hw.print("By S. Moreno");
        return;
    case Mode::temperature:
        sensor = &temp_sensor;
        hw.print("Temps (C):");
        break;
    case Mode::humidity:
        sensor = &hum_sensor;
        hw.print("Humid (%):");
        break;
    }
    if (sensor == nullptr) return;

    hw.setCursor(11,0);
    hw.print(sensor->getReading(),0);
    hw.setCursor(0,1);
    hw.print("lo: ");
    hw.print(sensor->getMin(),0);
    hw.print(" hi: ");
    hw.print(sensor->getMax(),0);
}

void Display::togglePrintMode(bool button_pressed)
{
    if (button_pressed && print_mode == Mode::temperature)
        print_mode = Mode::humidity;
    else if ((button_pressed && print_mode == Mode::humidity)
            || print_mode == Mode::welcome)
        print_mode = Mode::temperature;
}