#pragma once
#include <Wire.h>
#include <stdint.h>

class GenericI2CSensorBase
{
public:
    virtual bool begin() = 0;
    virtual bool update() = 0;
    virtual const char *getSensorName() const = 0;
    virtual const void *getData() const = 0;
    bool isValid() { return isValid_Bool; }
    virtual ~GenericI2CSensorBase() {};
    virtual Config::I2CSensorType getSensorType() const { return Config::I2CSensorType::None; }

protected:
    bool isValid_Bool = false;
    TwoWire *wire = nullptr;
    uint8_t i2cAddress = 0;
};

class GenericAnalogSensorBase
{
public:
};