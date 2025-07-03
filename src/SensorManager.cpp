#include <SensorManager.h>

bool SensorManager::beginAll()
{
    if (!wire->begin(Config::I2C_SDA_PIN, Config::I2C_SCL_PIN))
    {
        DEBUG_PRINTLN("Failed to initialize I2C Wire.");
        return false;
    }
    DEBUG_PRINTLN("I2C Wire initialized successfully.");

    if (!beginAnalogSensors())
    {
        DEBUG_PRINTLN("Failed to initialize analog sensors.");
        return false;
    }

    if (!beginI2CSensors())
    {
        DEBUG_PRINTLN("Failed to initialize I2C sensors.");
        return false;
    }

    DEBUG_PRINTLN("All Sensors initialized.");
    return true;
}

bool SensorManager::updateAll()
{
    if (!updateAnalogSensors())
    {
        DEBUG_PRINTLN("Failed to update analog sensors.");
        return false;
    }

    if (!updateI2CSensors())
    {
        DEBUG_PRINTLN("Failed to update I2C sensors.");
        return false;
    }

    DEBUG_PRINTLN("All Sensors updated successfully.");
    return true;
}

bool SensorManager::beginI2CSensors()
{
    DEBUG_PRINTLN("Starting I2C scanner");
    for (uint8_t i = 0; i < 127; i++)
    {
        wire->beginTransmission(i);
        if (!wire->endTransmission() == 0)
        {
            DEBUG_PRINT("No device found at address 2x");
            DEBUG_PRINTLN(i);
            continue;
        }
        DEBUG_PRINT("Device found at address 2x");
        DEBUG_PRINTLN(i);
        for (int j = 0; j < Config::numberOfKnownI2CSensors; j++)
        {
            if (i != Config::I2CSensorTable[j].address)
                continue;
            switch (Config::I2CSensorTable[j].type)
            {
            case Config::I2CSensorType::BMP280:
                i2cSensors[numberOfInitializedI2CSensors] = new BMP280_Wrapper;
                i2cSensors[numberOfInitializedI2CSensors]->begin(i2cAddress, &wire);
                numberOfInitializedI2CSensors++;
                break;
            case Config::I2CSensorType::None:
                DEBUG_PRINTLN("No sensor type defined for this address, skipping initialization.");
                break;
            default:
                DEBUG_PRINTLN("Unknown I2C sensor type, skipping initialization.");
                break;
            }
        }
    }
    return true;
}