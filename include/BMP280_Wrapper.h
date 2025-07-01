#pragma once
#include <config.h>
#include <GenericSensorBase.h>
#include <Adafruit_BMP280.h>

class BMP280_Wrapper : public GenericSensorBase
{
public:
    Struct Data
    {
        float temperature = NAN;
        float pressure = NAN;
        float altitude = NAN;
    }
    bool begin(uint8_t _i2cAddress, TwoWire &_wire) override;
    bool update() override;
    const char *getSensorName() const override;
    {
        return "BMP280";
    }
    const void *getData() const override
    {
        return &data;
    }
    const bool isValid() const override
    {
        return isValid;
    }

private:
    void setSampling();
    Adafruit_BMP280 sensor; // Create an instance of the BMP280 sensor
    Data data;
    uint8_t i2cAddress;
    bool isValid = false; // Flag to indicate if the sensor data is valid
};
