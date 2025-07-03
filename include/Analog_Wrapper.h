#pragma once
#include <config.h>
#include <GenericSensorBase.h>
#include <Arduino.h>

class Analog_Wrapper : public GenericAnalogSensorBase
{
public:
    // Analog_Wrapper(uint8_t _pin, AnalogSensorType _type)
    // {
    //     pin = _pin;
    //     type = _type;
    // }
    // bool initialize();
    // float readValue();

private:
    // uint8_t pin;
    // AnalogSensorType type;
    // bool initialized = false;
};
