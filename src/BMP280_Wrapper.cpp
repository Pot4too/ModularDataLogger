#include "BMP280_Wrapper.h"

bool BMP280_Wrapper::begin()
{
    sensor = Adafruit_BMP280(wire);
    if (!sensor.begin(i2cAddress))
    {
        LOCAL_DEBUG_PRINTLN("BMP280 sensor initialization failed.");
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
        LOCAL_DEBUG_PRINTLN("Failed to take forced measurement from BMP280.");
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
    LOCAL_DEBUG_PRINT("BMP280 Sensor Data: ");
    LOCAL_DEBUG_PRINT("Temperature: ");
    LOCAL_DEBUG_PRINT(data.temperature);
    LOCAL_DEBUG_PRINT(" °C, Pressure: ");
    LOCAL_DEBUG_PRINT(data.pressure);
    LOCAL_DEBUG_PRINT(" hPa, Altitude: ");
    LOCAL_DEBUG_PRINT(data.altitude);
    LOCAL_DEBUG_PRINTLN(" m");
    LOCAL_DEBUG_PRINTLN("Sensor data is valid: " + String(isValid_Bool ? "true" : "false"));
    LOCAL_DEBUG_PRINTLN("Sensor I2C Address: 0x" + String(i2cAddress, HEX));
    LOCAL_DEBUG_PRINTLN("Sensor Type: " + String(getSensorType() == Config::I2CSensorType::BMP280 ? "BMP280" : "Unknown"));
    LOCAL_DEBUG_PRINTLN("Sensor Name: " + String(getSensorName()));
}

bool BMP280_Wrapper::logDataToSd(File *dataFile)
{
    if (!isValid())
    {
        LOCAL_DEBUG_PRINTLN("BMP280 sensor data is not valid, skipping logging.");
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
    LOCAL_DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        // LOCAL_DEBUG_PRINTLN("SD printing: " + String(getSensorName()));
        dataFile->print(getSensorName());
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void BMP280_Wrapper::createDataTypesHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        // LOCAL_DEBUG_PRINTLN("SD printing: " + String(namesOfData()[i]));
        dataFile->print(namesOfData()[i]);
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}