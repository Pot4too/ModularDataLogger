#include "AHT20_Wrapper.h"

/**
 * @brief Initializes AHT20 sensor
 *
 * @return true if AHT20 initialized correctly, false otherwise
 */
bool AHT20_Wrapper::begin()
{
    return sensor.begin();
}

/**
 * @brief Reads temperature and humidity from the AHT20 sensor.
 *
 * @return True if data updated succesfully, false otherwise
 */
bool AHT20_Wrapper::update()
{
    data.temperature = sensor.getTemperature();
    data.humidity = sensor.getHumidity();
    bool temperatureIsValid = data.temperature < -40 || data.temperature > 86;
    bool humidityIsValid = data.humidity < 0 || data.humidity > 100;
    if (temperatureIsValid || humidityIsValid)
    {
        DEBUG_PRINTLN("AHT20_Wrapper.h update() failed");
        isValid_Bool = false;
        return false;
    }
    isValid_Bool = true;
    return true;
}

const void AHT20_Wrapper::debugPrintData() const
{
    DEBUG_PRINT("AHT20 Sensor Data: ");
    DEBUG_PRINT("Temperature: ");
    DEBUG_PRINT(data.temperature);
    DEBUG_PRINT(" °C, Humidity: ");
    DEBUG_PRINT(data.humidity);
    DEBUG_PRINTLN(" % RH");
    DEBUG_PRINTLN("Sensor data is valid: " + String(isValid_Bool ? "true" : "false"));
    DEBUG_PRINTLN("Sensor I2C Address: 0x" + String(i2cAddress, HEX));
    DEBUG_PRINTLN("Sensor Type: " + String(getSensorType() == Config::I2CSensorType::AHT20 ? "AHT20" : "Unknown"));
    DEBUG_PRINTLN("Sensor Name: " + String(getSensorName()));
}

bool AHT20_Wrapper::logDataToSd(File *dataFile)
{
    if (!isValid())
    {
        DEBUG_PRINTLN("AHT20 sensor data is not valid, skipping logging.");
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
    dataFile->print(data.humidity);
    return true;
}

void AHT20_Wrapper::createNameHeader(File *dataFile)
{
    DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < numberOfUniqueData(); i++)
    {
        dataFile->print(getSensorName());
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void AHT20_Wrapper::createDataTypesHeader(File *dataFile)
{
    DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < numberOfUniqueData(); i++)
    {
        dataFile->print(namesOfData()[i]);
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}
