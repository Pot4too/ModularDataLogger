#include <AHT20_Wrapper.h>

/**
 * @brief Initializes the AHT20 sensor.
 *
 * @param wire Reference to the TwoWire object for I2C communication.
 * @param address I2C address of the AHT20 sensor (default is 0x38).
 * @return true if initialization is successful, false otherwise.
 */
bool AHT20_Wrapper::begin(TwoWire &wire, uint8_t address)
{
    AHT20 aht(address); // Initialize AHT20 with the default address
    return aht.begin();
}

/**
 * @brief Reads temperature and humidity from the AHT20 sensor.
 *
 * @return SensorData_AHT20 structure containing temperature, humidity, and validity flag.
 */
SensorData_AHT20 AHT20_Wrapper::read()
{
    SensorData_AHT20 data;
    data.temperature = aht.getTemperature();
    data.humidity = aht.getHumidity();
    data.valid = !isnan(data.temperature) && !isnan(data.humidity);
    return data;
}