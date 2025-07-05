#pragma once
#include "config.h"
#include "GenericSensorBase.h"
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

    BMP280_Wrapper(int8_t _i2cAddress, TwoWire &_wire)
    {
        i2cAddress = _i2cAddress;
        wire = &_wire;
    }
    bool begin() override;
    bool update() override;
    const char *getSensorName() const override { return "BMP280"; }
    const void *getData() const override { return &data; }
    Config::I2CSensorType getSensorType() const override { return Config::I2CSensorType::BMP280; }
    const void debugPrintData() const override;

private:
    void setSampling();
    Adafruit_BMP280 sensor; // Create an instance of the BMP280 sensor
    Data data;
};
