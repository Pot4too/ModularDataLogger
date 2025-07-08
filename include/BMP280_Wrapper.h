#pragma once

// #define LOCAL_DEBUG

#include "config.h"
#include "GenericSensorBase.h"
#include <Adafruit_BMP280.h>

#if defined(LOCAL_DEBUG) || defined(GLOBAL_DEBUG_OVERRIDE)
#define LOCAL_DEBUG_PRINT DEBUG_PRINT
#define LOCAL_DEBUG_PRINTLN DEBUG_PRINTLN
#else
#define LOCAL_DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x)
#endif // DEBUG

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

    bool logDataToSd(File *dataFile) override;
    void createNameHeader(File *dataFile) override;
    void createDataTypesHeader(File *dataFile) override;

private:
    void setSampling();
    Adafruit_BMP280 sensor;
    Data data;

    // Define the field names for the BMP280 sensor data
    static constexpr const char *FIELD_NAMES[] = {"Temperature", "Pressure", "Altitude"};
    const char *const *namesOfData() const override { return FIELD_NAMES; }
    const uint8_t numberOfUniqueData() const override { return sizeof(FIELD_NAMES) / sizeof(FIELD_NAMES[0]); }
};
