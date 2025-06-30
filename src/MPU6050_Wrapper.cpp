#include <MPU6050_Wrapper.h>

/**
 * @brief Initializes the MPU6050 sensor.
 *
 * @param address I2C address of the MPU6050 sensor, default is 0x68.
 * @return true if initialization is successful, false otherwise.
 * @param wire Reference to the TwoWire object for I2C communication.
 * @param sensor_id
 */
bool MPU6050_Wrapper::begin(uint8_t address, TwoWire &wire, int32_t sensor_id = -1)
{
    if (!mpu.begin(address, &wire, sensor_id))
        return false;
    setSenosorConfiguration();
    return true;
}

/**
 * @brief  Reads data from the MPU6050 sensor.
 *
 * @return SensorData_MPU6050 struct and validity check.
 */
SensorData_MPU6050 MPU6050_Wrapper::read()
{
    SensorData_MPU6050 data;
    sensors_event_t _acceleration, _rotation, _temperature;
    if (!mpu.getEvent(&_acceleration, &_rotation, &_temperature))
        return data;
    data.ax = _acceleration.acceleration.x; // Acceleration in m/s^2
    data.ay = _acceleration.acceleration.y; // Acceleration in m/s^2
    data.az = _acceleration.acceleration.z; // Acceleration in m/s^2
    data.gx = _rotation.gyro.x;             // Angular velocity in rad/s
    data.gy = _rotation.gyro.y;             // Angular velocity in rad/s
    data.gz = _rotation.gyro.z;             // Angular velocity in rad/s
    data.temp = _temperature.temperature;   // Temperature in °C
    data.valid = true;                      // Mark data as valid
    return data;
}

/**
 * @brief Sets the configuration for the MPU6050 sensor.
 *
 */
void MPU6050_Wrapper::setSenosorConfiguration()
{
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
