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