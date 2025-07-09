#pragma once

#define LOCAL_DEBUG

#include <config.h>
#include <GenericSensorBase.h>
#include <Adafruit_MPU6050.h>

#if defined(LOCAL_DEBUG) || defined(GLOBAL_DEBUG_OVERRIDE)
#define LOCAL_DEBUG_PRINT DEBUG_PRINT
#define LOCAL_DEBUG_PRINTLN DEBUG_PRINTLN
#else
#define LOCAL_DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x)
#endif // DEBUG

class MPU6050_Wrapper : public GenericI2CSensorBase
{
public:
    struct Data
    {
        float ax, ay, az; // Acceleration in m/s^2
        float gx, gy, gz; // Angular velocity in rad/s
        float temp;       // Temperature in °C
        SensorData_MPU6050() : ax(NAN), ay(NAN), az(NAN), gx(NAN), gy(NAN), gz(NAN), temp(NAN) {}
    };

    MPU6050_Wrapper(uint8_t _address, TwoWire &_wire);

    bool begin() ovverride;
    bool update() ovverride;

    const char *getSensorName() const ovverride { return "MPU6050"; }
    bool isValid() const { return isValid_Bool; }
    const void *getData() const ovverride { return &data; }
    Config::I2CSensorType getSensorType() const ovverride { return Config::I2CSensorType::MPU6050; }

    const void debugPrintData() const ovverride;

    bool logDataToSd(File *dataFile) ovverride;
    void createNameHeader(File *dataFile) ovverride;
    void createDataTypesHeader(File *dataFile) ovverride;

private:
    Adafruit_MPU6050 sensor;
    Data data;

    uint8_t i2cAddress;
    TwoWire *wire;
    bool isValid_Bool = false;
    int32_t sensorID = -1;

    void setSenosorConfiguration();

    static constexpr const char *FIELD_NAMES[] = {"aX", "aY", "aZ", "gX", "gY", "gZ", "Temperature"};
    const uint8_t numberOfUniqueData() const ovverride { return sizeof(FIELD_NAMES) / sizeof(FIELD_NAMES[0]); }
    const char *const *namesOfData() const ovverride { return FIELD_NAMES; }
};