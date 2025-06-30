#pragma once
#include <config.h>
#include <AHT20.h>

struct SensorData_AHT20
{
    float temperature = NAN; // Temperature in °C
    float humidity = NAN;    // Humidity in % RH
    bool valid = false;      // Validity flag
};

class AHT20_Wrapper
{
public:
    bool begin(TwoWire &wire, uint8_t address = 0x38);
    SensorData_AHT20 read();

private:
    AHT20 aht; // Create an instance of the AHT20 sensor
};