#pragma once
#include "config.h"
#include "GenericSensorBase.h"
#include <Wire.h>

//* Sensor wrappers
#include "BMP280_Wrapper.h"
// #include <AHT20_Wrapper.h>
// #include <Analog_Wrapper.h>
// #include <MPU6050_Wrapper.h>

class SensorManager
{
public:
    bool beginAll();
    bool updateAll();
    TwoWire &getI2CWire()
    {
        return *mainWire;
    }
    void testBMP280();

private:
    bool beginAnalogSensors();
    bool beginI2CSensors();
    bool updateAnalogSensors();
    bool updateI2CSensors();

    TwoWire *mainWire = &Wire;

    uint8_t numberOfInitializedI2CSensors = 0;
    GenericI2CSensorBase *i2cSensors[Config::maxI2CSensors] = {nullptr};
};
