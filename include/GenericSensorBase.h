#pragma once
#include <Wire.h>
#include <stdint.h>
#include "dataLogger.h"

class GenericI2CSensorBase : public GenericSensorLogger
{
public:
    virtual bool begin() = 0;
    virtual bool update() = 0;
    virtual const char *getSensorName() const = 0;
    virtual const void *getData() const = 0;
    bool isValid() { return isValid_Bool; }
    virtual ~GenericI2CSensorBase() {};
    virtual Config::I2CSensorType getSensorType() const { return Config::I2CSensorType::None; }
    virtual const void debugPrintData() const;

protected:
    bool isValid_Bool = false;
    TwoWire *wire = nullptr;
    uint8_t i2cAddress = 0;
};

class GenericAnalogSensorBase : public GenericSensorLogger
{
public:
    virtual bool update() = 0;
    virtual bool begin() = 0;
    virtual const char *getSensorName() const = 0;
    virtual const void *getData() const = 0;
    virtual Config::AnalogSensorType getSensorType() const { return Config::AnalogSensorType::None; }
    virtual ~GenericAnalogSensorBase() {};
    virtual const void debugPrintData() const;

protected:
    bool isDataValid = false;
    uint8_t pin = 0;
    float data = 0.0f;
    bool isSensorPresent() { return (analogRead(pin) * (3.3 / 4095.0)) < 0.1 ? true : false; }
};