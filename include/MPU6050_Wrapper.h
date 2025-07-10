/** @file MPU6050_Wrapper.h
 * @brief Wrapper for the MPU6050 sensor using Adafruit's library.
 *
 * This file defines the MPU6050_Wrapper class which provides an interface to interact with the MPU6050 sensor.
 * It includes methods for initialization, data retrieval, and logging to SD card.
 */
#pragma once

// Local debug flag to enable/disable debug prints
#define LOCAL_DEBUG

// Include necessary headers
#include <config.h>
#include <GenericSensorBase.h>
#include <Adafruit_MPU6050.h>

// Debug print macros
#if defined(LOCAL_DEBUG) || defined(GLOBAL_DEBUG_OVERRIDE)
#define LOCAL_DEBUG_PRINT(x) DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x) DEBUG_PRINTLN(x)
#else
#define LOCAL_DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x)
#endif // DEBUG

/**
 * @brief Wrapper class for the MPU6050 sensor.
 * This class provides methods to initialize the sensor, read data from it,
 * and log the data to an SD card.
 */
class MPU6050_Wrapper : public GenericI2CSensorBase
{
public:
    /**
     * @brief Structure to hold the sensor data.
     * Contains acceleration, angular velocity, and temperature readings.
     */
    struct Data
    {
        float aX, aY, aZ;  // Acceleration in m/s^2
        float gX, gY, gZ;  // Angular velocity in rad/s
        float temperature; // Temperature in °C
    };

    /**
     * @brief Constructor for the MPU6050_Wrapper class.
     * Initializes the sensor with the given I2C address and wire interface.
     *
     * @param _address I2C address of the MPU6050 sensor.
     * @param _wire Reference to the TwoWire object for I2C communication.
     */
    MPU6050_Wrapper(uint8_t _address, TwoWire &_wire);

    /**
     * @brief Initializes the MPU6050 sensor.
     * Sets up the sensor with the specified I2C address and wire interface.
     *
     * @return true if initialization is successful, false otherwise.
     */
    bool begin() override;

    /**
     * @brief Updates the sensor data.
     * Reads the current data from the MPU6050 sensor.
     *
     * @return true if data is successfully updated, false otherwise.
     */
    bool update() override;

    /**
     * @brief Gets the name of the sensor.
     *
     * @return The name of the sensor as a string.
     */
    const char *getSensorName() const override { return "MPU6050"; }

    /**
     * @brief Gets the data from the sensor.
     *
     * @return Pointer to the sensor data structure.
     */
    const void *getData() const override { return &data; }

    /**
     * @brief Gets the sensor type based on Config.h
     *
     * @return Sensor type.
     */
    Config::I2CSensorType getSensorType() const override { return Config::I2CSensorType::MPU6050; }

    /**
     * @brief Prints the sensor data to the debug console.
     * Outputs the acceleration, angular velocity, and temperature readings.
     */
    const void debugPrintData() const override;

    /**
     * @brief Logs the sensor data to an SD card.
     * Writes the sensor data to the specified file in CSV format.
     *
     * @param dataFile Pointer to the file where data will be logged.
     * @return true if logging is successful, false otherwise.
     */
    bool logDataToSd(File *dataFile) override;

    /**
     * @brief Creates the header for the sensor name in the data file.
     * Writes the sensor name to the specified file.
     *
     * @param dataFile Pointer to the file where the header will be created.
     */
    void createNameHeader(File *dataFile) override;

    /**
     * @brief Creates the header for the data types in the data file.
     * Writes the data types to the specified file.
     *
     * @param dataFile Pointer to the file where the data types header will be created.
     */
    void createDataTypesHeader(File *dataFile) override;

private:
    Adafruit_MPU6050 sensor;
    Data data; // Sensor data structure

    int32_t sensorID = -1;

    /**
     * @brief Sets the configuration for the MPU6050 sensor.
     * Configures the accelerometer and gyroscope ranges and filter bandwidth.
     */
    void setSenosorConfiguration();

    // Define the field names for the MPU6050 sensor data
    static constexpr const char *FIELD_NAMES[] = {"aX", "aY", "aZ", "gX", "gY", "gZ", "Temperature"};

    /**
     * @brief Gets the number of unique data fields for the MPU6050 sensor.
     *
     * @return The number of unique data fields.
     */
    const uint8_t numberOfUniqueData() const override { return sizeof(FIELD_NAMES) / sizeof(FIELD_NAMES[0]); }

    /**
     * @brief Gets the names of the data fields for the MPU6050 sensor.
     *
     * @return Pointer to an array of field names.
     */
    const char *const *namesOfData() const override { return FIELD_NAMES; }
};