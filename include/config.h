#pragma once
//! Debuging
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

//! Pin configuration
//* I2C Pins
#define I2C_SCL_PIN 22
#define I2C_SDA_PIN 21

//* SPI Pins
#define SPI_MOSI_PIN 23
#define SPI_MISO_PIN 19
#define SPI_SCK_PIN 18
#define SD_CS_PIN 5

//* Analog Sensor Pins
//? Pin definitions
#define A0_PIN 36
#define A1_PIN 39

//? Pin Sensor Definitions
#define A0_Sensor CapacitiveMoisture
#define A1_Sensor MAX4466

//* Digital Pins
//? Pin definitions
#define D0_PIN -1
#define D1_PIN -1
#define D2_PIN -1

//? Pin Sensor Definitions
#define D0_Sensor AHT20

//* BMP280 sensor
#define seaLevelPressure 1013.25 // Default sea level pressure in hPa

#pragma once
#define DEBUG // ✅ For preprocessor conditionals (e.g., #ifdef DEBUG)

namespace Config
{

#ifdef DEBUG
    constexpr bool DEBUG_MODE = true; // ✅ Optional: for C++ logic
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#else
    constexpr bool DEBUG_MODE = false;
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#endif

    constexpr int SERIAL_BAUD_RATE = 115200;

    //* I2C
    constexpr int I2C_SDA_PIN = 21;
    constexpr int I2C_SCL_PIN = 22;

    //* SPI
    constexpr int SPI_MOSI_PIN = 23;
    constexpr int SPI_MISO_PIN = 19;
    constexpr int SPI_SCK_PIN = 18;
    constexpr int SD_CS_PIN = 5; // SD ChipSelect pin

    //* Analog Sensors
    constexpr int ANALOG_SENSOR_0_PIN = 36;
    constexpr int ANALOG_SENSOR_1_PIN = 39;

    enum class AnalogSensorType
    {
        None,
        MAX4466,
        CapacitiveMoisture,
        MQ135,
        Generic
    };

    constexpr AnalogSensorType ANALOG_SENSOR_0_TYPE = AnalogSensorType::CapacitiveMoisture;
    constexpr AnalogSensorType ANALOG_SENSOR_1_TYPE = AnalogSensorType::MAX4466;
    constexpr AnalogSensorType ANALOG_SENSOR_2_TYPE = AnalogSensorType::None;
    constexpr AnalogSensorType ANALOG_SENSOR_3_TYPE = AnalogSensorType::None;
    constexpr AnalogSensorType ANALOG_SENSOR_4_TYPE = AnalogSensorType::None;

    enum class I2CSensorType
    {
        None,
        BMP280,
        AHT20,
        MPU6050,
        BH1750
    };

    constexpr I2CSensorType I2C_SENSOR_0_TYPE = I2CSensorType::BMP280;
    constexpr uint8_t I2C_SENSOR_0_ADDRESS = 0x76;

    constexpr I2CSensorType I2C_SENSOR_1_TYPE = I2CSensorType::AHT20;
    constexpr uint8_t I2C_SENSOR_1_ADDRESS = 0x38;

    constexpr I2CSensorType I2C_SENSOR_2_TYPE = I2CSensorType::MPU6050;
    constexpr uint8_t I2C_SENSOR_2_ADDRESS = 0x68;

    constexpr I2CSensorType I2C_SENSOR_0_TYPE = I2CSensorType::None;
    constexpr uint8_t I2C_SENSOR_0_ADDRESS = 0x00;

    constexpr I2CSensorType I2C_SENSOR_1_TYPE = I2CSensorType::None;
    constexpr uint8_t I2C_SENSOR_1_ADDRESS = 0x00;

    constexpr I2CSensorType I2C_SENSOR_2_TYPE = I2CSensorType::None;
    constexpr uint8_t I2C_SENSOR_2_ADDRESS = 0x00;

    constexpr float SEA_LEVEL_PRESSURE_HPA = 1013.25f;

} // namespace Config
