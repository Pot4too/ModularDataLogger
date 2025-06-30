#pragma once
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

//* Digital Pins
//? Pin definitions
#define D0_PIN 2
#define D1_PIN 3
#define D2_PIN 4

//? Pin Sensor Definitions
#define D0_Sensor AHT20

//* BMP280 sensor
#define seaLevelPressure 1013.25 // Default sea level pressure in hPa
