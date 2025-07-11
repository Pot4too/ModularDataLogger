#pragma once
//! Includes
#include "config.h"
#include "GenericSensorBase.h"
#include <Wire.h>
#include <string.h>

//* Sensor wrappers
#include "BMP280_Wrapper.h"
#include <AHT20_Wrapper.h>
#include <MPU6050_Wrapper.h>
#include <MAX4466_Wrapper.h>

//* Data Logger
#include <dataLogger.h>

class SensorManager
{
public:
    bool beginAll();
    bool updateAll();
    TwoWire &getI2CWire() { return *mainWire; }
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

    GenericI2CSensorBase *createI2CSensorInstance(Config::I2CSensorType type, uint8_t i2cAddress);
    GenericAnalogSensorBase *createAnalogSensorInstance(Config::AnalogSensorType type, uint8_t pin);

    TwoWire *mainWire = &Wire;
    DataLogger *dataLogger;
    bool dataLoggerInitialized = false;
    SPIClass mainSPI;

    uint8_t numberOfInitializedI2CSensors = 0;
    GenericI2CSensorBase *i2cSensors[Config::maxI2CSensors] = {nullptr};

    uint8_t numberOfInitializedAnalogSensors = 0;
    GenericAnalogSensorBase *analogSensors[Config::AnalogSensorCount] = {nullptr};
};
