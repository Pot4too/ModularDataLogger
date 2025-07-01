#pragma once
#include <config.h>
#include <Wire.h>
#include <AHT20_Wrapper.h>
#include <Analog_Wrapper.h>
#include <BMP280_Wrapper.h>
#include <MPU6050_Wrapper.h>

Class SensorManager
{
public:
    bool begin();

private:
    bool initAnalogSensors();
    bool initI2cSensors();
}
