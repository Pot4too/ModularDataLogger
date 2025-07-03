#pragma once
#include <config.h>
#include <GenericSensorBase.h>
#include <Adafruit_BMP280.h>

class BMP280_Wrapper : public GenericI2CSensorBase
{
public:
    struct Data
    {
        float temperature = NAN;
        float pressure = NAN;
        float altitude = NAN;
    };
    bool begin(uint8_t _i2cAddress, TwoWire &_wire);
    bool update();
    const char *getSensorName()
    {
        return "BMP280";
    }
    const void *getData()
    {
        return &data;
    }

private:
    void setSampling();
    Adafruit_BMP280 sensor; // Create an instance of the BMP280 sensor
    Data data;
};
