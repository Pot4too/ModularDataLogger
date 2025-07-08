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
        LOCAL_DEBUG_PRINTLN("AHT20_Wrapper.h update() failed");
        isValid_Bool = false;
        return false;
    }
    isValid_Bool = true;
    return true;
}

const void AHT20_Wrapper::debugPrintData() const
{
    LOCAL_DEBUG_PRINT("AHT20 Sensor Data: ");
    LOCAL_DEBUG_PRINT("Temperature: ");
    LOCAL_DEBUG_PRINT(data.temperature);
    LOCAL_DEBUG_PRINT(" °C, Humidity: ");
    LOCAL_DEBUG_PRINT(data.humidity);
    LOCAL_DEBUG_PRINTLN(" % RH");
    LOCAL_DEBUG_PRINTLN("Sensor data is valid: " + String(isValid_Bool ? "true" : "false"));
    LOCAL_DEBUG_PRINTLN("Sensor I2C Address: 0x" + String(i2cAddress, HEX));
    LOCAL_DEBUG_PRINTLN("Sensor Type: " + String(getSensorType() == Config::I2CSensorType::AHT20 ? "AHT20" : "Unknown"));
    LOCAL_DEBUG_PRINTLN("Sensor Name: " + String(getSensorName()));
}

bool AHT20_Wrapper::logDataToSd(File *dataFile)
{
    if (!isValid())
    {
        LOCAL_DEBUG_PRINTLN("AHT20 sensor data is not valid, skipping logging.");
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
    LOCAL_DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        dataFile->print(getSensorName());
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void AHT20_Wrapper::createDataTypesHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        dataFile->print(namesOfData()[i]);
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}
