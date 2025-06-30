#pragma once
#include <config.h>
#include <Adafruit_MPU6050.h>

struct SensorData_MPU6050
{
    float ax, ay, az; // Acceleration in m/s^2
    float gx, gy, gz; // Angular velocity in rad/s
    float temp;       // Temperature in °C
    bool valid;

    SensorData_MPU6050() : ax(NAN), ay(NAN), az(NAN), gx(NAN), gy(NAN), gz(NAN), temp(NAN), valid(false) {}
};

class MPU6050_Wrapper
{
public:
    bool begin(uint8_t address, TwoWire &wire, int32_t sensor_id);
    SensorData_MPU6050 read();

private:
    void setSenosorConfiguration();
    Adafruit_MPU6050 mpu;
};
