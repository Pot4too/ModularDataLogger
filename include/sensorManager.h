#pragma once
#include "config.h"
#include "GenericSensorBase.h"
#include <Wire.h>
#include <string.h>

//* Sensor wrappers
#include "BMP280_Wrapper.h"
#include <AHT20_Wrapper.h>
// #include <Analog_Wrapper.h>
// #include <MPU6050_Wrapper.h>
#include <dataLogger.h>

class SensorManager
{
public:
    bool beginAll();
    bool updateAll();
    TwoWire &getI2CWire()
    {
        return *mainWire;
    }
    bool logSensorsDataToSd();
    void testI2CSensors();

private:
    bool beginAnalogSensors();
    bool beginI2CSensors();
    bool updateAnalogSensors();
    bool updateI2CSensors();
    void beginSPI();
    bool beginDataLogger();
    void createLogFileHeader();

    GenericI2CSensorBase *createSensorInstance(Config::I2CSensorType type, uint8_t i2cAddress);

    TwoWire *mainWire = &Wire;
    DataLogger *dataLogger;
    bool dataLoggerInitialized = false;

    uint8_t numberOfInitializedI2CSensors = 0;
    GenericI2CSensorBase *i2cSensors[Config::maxI2CSensors] = {nullptr};
};
