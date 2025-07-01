#pragma once
#include <config.h>
#include <Arduino.h>

typedef enum
{
    CapacitiveMoisture, // Capacitive Moisture Sensor
    MQ135,              // Air quality sensor
    MAX4466,            // Microphone sensor
    GenericAnalog       // Generic analog sensor
} AnalogSensorType;

class Analog_Wrapper
{
public:
    Analog_Wrapper(uint8_t _pin, AnalogSensorType _type)
    {
        pin = _pin;
        type = _type;
    }
    bool initialize();
    float readValue();

private:
    uint8_t pin;
    AnalogSensorType type;
    bool initialized = false;
};
