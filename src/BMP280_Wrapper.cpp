#include <BMP280_Wrapper.h>

/**
 * @brief Initializes the BMP280 sensor.
 *
 * @param address The I2C address of the BMP280 sensor, default is 0x76.
 * @return true if initialization is successful, false otherwise.
 */
bool BMP280_Wrapper::begin(uint8_t address)
{
    if (!bmp.begin(address))
        return false;
    BMP280_Wrapper::bmp.setSampling();
    return true;
}

/**
 * @brief Reads data from the BMP280 sensor.
 *
 * @return SensorData_BMP280 struct with validity check.
 */
SensorData_BMP280 BMP280_Wrapper::read()
{
    SensorData_BMP280 data;
    if (!bmp.takeForcedMeasurement())
        return data; // Return invalid data if measurement fails
    data.temperature = bmp.readTemperature();
    data.pressure = bmp.readPressure() / 100.0F;        // Convert pressure to hPa
    data.altitude = bmp.readAltitude(seaLevelPressure); // Calculate altitude based on sea level pressure
    data.valid = true;                                  // Mark data as valid
    return data;
}

/**
 * @brief Sets the sampling configuration for the BMP280 sensor.
 *
 * @return Sets FORCED mode for BMP280.
 */
void BMP280_Wrapper::setSampling()
{
    BMP280_Wrapper::bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     // Operating Mode
                                    Adafruit_BMP280::SAMPLING_X16,    // Temperature sampling
                                    Adafruit_BMP280::SAMPLING_X16,    // Pressure sampling
                                    Adafruit_BMP280::FILTER_X16,      // Filtering
                                    Adafruit_BMP280::STANDBY_MS_500); // Standby time
}
