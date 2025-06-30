#pragma once
#include <config.h>
#include <Adafruit_BMP280.h>

struct SensorData_BMP280
{
    float temperature = NAN;
    float pressure = NAN;
    float altitude = NAN;
    bool valid = false;
};

class BMP280_Wrapper
{
public:
    bool begin(uint8_t address);
    SensorData_BMP280 read();

private:
    void setSampling();
    Adafruit_BMP280 bmp; // Create an instance of the BMP280 sensor
};
