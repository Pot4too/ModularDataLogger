#include <BMP280_Wrapper.h>

bool BMP280_Wrapper::begin(uint8_t _i2cAddress, TwoWire &_wire)
{
    i2cAddress = _i2cAddress;
    *wire = _wire;
    sensor = Adafruit_BMP280(&_wire);
    if (!sensor.begin(i2cAddress))
    {
        DEBUG_PRINTLN("BMP280 sensor initialization failed.");
        return false;
    }
    setSampling();
    isValid_Bool = true;
    return true;
}

bool BMP280_Wrapper::update()
{
    if (!BMP280_Wrapper::sensor.takeForcedMeasurement())
    {
        DEBUG_PRINTLN("Failed to take forced measurement from BMP280.");
        isValid_Bool = false;
        return false; // Return false if measurement fails
    }
    data.temperature = sensor.readTemperature();
    data.pressure = sensor.readPressure() / 100.0F;
    data.altitude = sensor.readAltitude(Config::SEA_LEVEL_PRESSURE_HPA);
    isValid_Bool = true;
    return true;
}

/**
 * @brief Sets the sampling configuration for the BMP280 sensor.
 *
 * @return Sets FORCED mode for BMP280.
 */
void BMP280_Wrapper::setSampling()
{
    sensor.setSampling(Adafruit_BMP280::MODE_FORCED,     // Operating Mode
                       Adafruit_BMP280::SAMPLING_X16,    // Temperature sampling
                       Adafruit_BMP280::SAMPLING_X16,    // Pressure sampling
                       Adafruit_BMP280::FILTER_X16,      // Filtering
                       Adafruit_BMP280::STANDBY_MS_500); // Standby time
}
