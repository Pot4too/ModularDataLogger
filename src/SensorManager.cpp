#include "SensorManager.h"

bool SensorManager::beginAll()
{
    if (!mainWire->begin(Config::I2C_SDA_PIN, Config::I2C_SCL_PIN))
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
        mainWire->beginTransmission(i);
        if (!mainWire->endTransmission() == 0)
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
                i2cSensors[numberOfInitializedI2CSensors] = new BMP280_Wrapper(Config::I2CSensorTable[j].address, *mainWire);
                if (!i2cSensors[numberOfInitializedI2CSensors]->begin())
                {
                    DEBUG_PRINTLN("Failed to initialize BMP280 sensor at address 0x" + String(i, HEX));
                    delete i2cSensors[numberOfInitializedI2CSensors];
                    i2cSensors[numberOfInitializedI2CSensors] = nullptr;
                    break;
                }
                numberOfInitializedI2CSensors++;
                break;
            case Config::I2CSensorType::AHT20:
                i2cSensors[numberOfInitializedI2CSensors] = new AHT20_Wrapper(Config::I2CSensorTable[j].address, *mainWire);
                if (!i2cSensors[numberOfInitializedI2CSensors]->begin())
                {
                    DEBUG_PRINTLN("Failed to initialize AHT20 sensor at address 0x" + String(i, HEX));
                    delete i2cSensors[numberOfInitializedI2CSensors];
                    i2cSensors[numberOfInitializedI2CSensors] = nullptr;
                    break;
                }
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

bool SensorManager::updateI2CSensors()
{
    for (uint8_t i = 0; i < numberOfInitializedI2CSensors; i++)
    {
        if (i2cSensors[i] == nullptr)
            continue;
        if (!i2cSensors[i]->update())
        {
            DEBUG_PRINTLN("Failed to update sensor: " + String(i2cSensors[i]->getSensorName()));
            continue;
        }
        // function to log data to sd card
    }
    return true;
}

void SensorManager::testI2CSensors()
{
    for (uint8_t i = 0; i < numberOfInitializedI2CSensors; i++)
    {
        if (i2cSensors[i] == nullptr)
            continue;
        if (i2cSensors[i]->isValid() == false)
        {
            DEBUG_PRINT("Sensor ");
            DEBUG_PRINT(i2cSensors[i]->getSensorName());
            DEBUG_PRINTLN(" is not valid, skipping data retrieval.");
            continue;
        }
        i2cSensors[i]->debugPrintData();
    }
}

bool SensorManager::beginAnalogSensors()
{
    return true;
}

bool SensorManager::updateAnalogSensors()
{
    return true;
}