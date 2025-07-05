#pragma once
#include "config.h"
#include "GenericSensorBase.h"
#include <AHT20.h>

class AHT20_Wrapper : public GenericI2CSensorBase
{
public:
    struct Data
    {
        float temperature = NAN; // Temperature in °C
        float humidity = NAN;    // Humidity in % RH
    };
    AHT20_Wrapper(uint8_t _i2cAddress, TwoWire &_wire)
    {
        i2cAddress = _i2cAddress;
        wire = &_wire;
        AHT20 x(i2cAddress);
        sensor = x;
    }
    bool begin() override;
    bool update() override;
    const char *getSensorName() const override { return "AHT20"; }
    const void *getData() const override { return &data; }
    Config::I2CSensorType getSensorType() const override { return Config::I2CSensorType::AHT20; }

private:
    AHT20 sensor;
    Data data;
};
