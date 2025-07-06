#include "BMP280_Wrapper.h"

bool BMP280_Wrapper::begin()
{
    sensor = Adafruit_BMP280(wire);
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

const void BMP280_Wrapper::debugPrintData() const
{
    DEBUG_PRINT("BMP280 Sensor Data: ");
    DEBUG_PRINT("Temperature: ");
    DEBUG_PRINT(data.temperature);
    DEBUG_PRINT(" °C, Pressure: ");
    DEBUG_PRINT(data.pressure);
    DEBUG_PRINT(" hPa, Altitude: ");
    DEBUG_PRINT(data.altitude);
    DEBUG_PRINTLN(" m");
    DEBUG_PRINTLN("Sensor data is valid: " + String(isValid_Bool ? "true" : "false"));
    DEBUG_PRINTLN("Sensor I2C Address: 0x" + String(i2cAddress, HEX));
    DEBUG_PRINTLN("Sensor Type: " + String(getSensorType() == Config::I2CSensorType::BMP280 ? "BMP280" : "Unknown"));
    DEBUG_PRINTLN("Sensor Name: " + String(getSensorName()));
}

bool BMP280_Wrapper::logDataToSd(File *dataFile)
{
    if (!isValid())
    {
        DEBUG_PRINTLN("BMP280 sensor data is not valid, skipping logging.");
        for (int i = 0; i < numberOfUniqueData(); i++)
        {
            dataFile->print("ERR");
            if (i != numberOfUniqueData() - 1)
                dataFile->print(",");
        }
        return false;
    }
    dataFile->print(data.temperature);
    dataFile->print(",");
    dataFile->print(data.pressure);
    dataFile->print(",");
    dataFile->print(data.altitude);
    return true;
}

void BMP280_Wrapper::createNameHeader(File *dataFile)
{
    DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < numberOfUniqueData(); i++)
    {
        dataFile->print(getSensorName());
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void BMP280_Wrapper::createDataTypesHeader(File *dataFile)
{
    DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < numberOfUniqueData(); i++)
    {
        dataFile->print(namesOfData()[i]);
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}