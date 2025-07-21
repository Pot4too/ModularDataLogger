#pragma once
#include <Arduino.h>

// comment out '#define DEBUG at the top of the config.h file' to disable debug mode
#define DEBUG
// #define GLOBAL_DEBUG_OVERRIDE

namespace Config
{
//! Debug configuration
#ifdef DEBUG
    constexpr bool DEBUG_MODE = true;
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
    constexpr bool DEBUG_MODE = false;
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

    //! Global definitions
    constexpr int SERIAL_BAUD_RATE = 115200;
    constexpr int LOOP_DELAY_MS = 3000;

    //* SPI
    constexpr int SPI_MOSI_PIN = 23;
    constexpr int SPI_MISO_PIN = 19;
    constexpr int SPI_SCK_PIN = 18;
    constexpr int SD_CS_PIN = 5; // SD ChipSelect pin
    constexpr int SPI_Frequency = 1000000;

    //! Analog Setup
    /**
     * @brief Enumeration for analog sensor types.
     * This enum defines the types of analog sensors that can be connected to the system.
     */
    enum class AnalogSensorType
    {
        None,
        MAX4466,
        CapacitiveMoisture,
        MQ135,
        Generic
    };

    /**
     * @brief  Structure representing an analog sensor.
     * This structure contains the pin number and type of the analog sensor.
     */
    struct AnalogSensor
    {
        uint8_t pin;
        AnalogSensorType type;
    };

    /**
     * @brief  Array of analog sensors.
     * This array contains the pin numbers and types of the analog sensors that can be connected
     * to the system. Each sensor is represented by an instance of the AnalogSensor structure.
     */
    constexpr AnalogSensor AnalogSensorTable[] = {
        {35, AnalogSensorType::CapacitiveMoisture},
        {34, AnalogSensorType::MAX4466},
        {0, AnalogSensorType::None},
        {0, AnalogSensorType::None},
        {0, AnalogSensorType::None}};

    constexpr uint8_t AnalogSensorCount = sizeof(AnalogSensorTable) / sizeof(AnalogSensorTable[0]);

    //! I2C Setup
    //* I2C Wire pins
    constexpr int I2C_SDA_PIN = 21;
    constexpr int I2C_SCL_PIN = 22;

    /**
     * @brief Enumeration for I2C sensor types.
     * This enum defines the types of sensors that can be connected via I2C.
     */
    enum class I2CSensorType
    {
        None,
        BMP280,
        AHT20,
        MPU6050,
        BH1750
    };

    /**
     * @brief Structure representing an I2C sensor.
     * This structure contains the I2C address and type of the sensor.
     */
    struct I2CSensor
    {
        uint8_t address;
        I2CSensorType type;
    };

    /**
     * @brief Array of I2C sensors.
     * This array contains the I2C addresses and types of the sensors that can be connected
     * to the system. Each sensor is represented by an instance of the I2CSensor structure.
     */
    constexpr I2CSensor I2CSensorTable[] = {
        {0x76, I2CSensorType::BMP280},
        {0x38, I2CSensorType::AHT20},
        {0x68, I2CSensorType::MPU6050},
        {0x23, I2CSensorType::BH1750}};

    constexpr uint8_t numberOfKnownI2CSensors = sizeof(I2CSensorTable) / sizeof(I2CSensorTable[0]);
    constexpr uint8_t maxI2CSensors = 10;

    // Sealevel pressure in hPa
    constexpr float SEA_LEVEL_PRESSURE_HPA = 1013.25f;

} // namespace Config
