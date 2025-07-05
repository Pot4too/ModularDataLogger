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
        }
    }
    return true;
}

void SensorManager::testBMP280()
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
        // if (strcmp(i2cSensors[i]->getSensorName(), "BMP280") == 0)
        // {
        //     const auto *dataBMP280 = static_cast<const BMP280_Wrapper::Data *>(i2cSensors[i]->getData());

        //     DEBUG_PRINT("BMP280 Sensor Data: ");
        //     DEBUG_PRINT("Temperature: ");
        //     DEBUG_PRINT(dataBMP280->temperature);
        //     DEBUG_PRINT(" °C, Pressure: ");
        //     DEBUG_PRINT(dataBMP280->pressure);
        //     DEBUG_PRINT(" hPa, Altitude: ");
        //     DEBUG_PRINT(dataBMP280->altitude);
        //     DEBUG_PRINTLN(" m");
        // }
        switch (i2cSensors[i]->getSensorType())
        {
        case Config::I2CSensorType::BMP280:
        {
            const auto *internalData = static_cast<const BMP280_Wrapper::Data *>(i2cSensors[i]->getData());

            DEBUG_PRINT("BMP280 Sensor Data: ");
            DEBUG_PRINT("Temperature: ");
            DEBUG_PRINT(internalData->temperature);
            DEBUG_PRINT(" °C, Pressure: ");
            DEBUG_PRINT(internalData->pressure);
            DEBUG_PRINT(" hPa, Altitude: ");
            DEBUG_PRINT(internalData->altitude);
            DEBUG_PRINTLN(" m");
            break;
        }

        case Config::I2CSensorType::AHT20:
        {
            const auto *internalData = static_cast<const AHT20_Wrapper::Data *>(i2cSensors[i]->getData());

            DEBUG_PRINT("AHT20 Sensor Data: ");
            DEBUG_PRINT("Temperature: ");
            DEBUG_PRINT(internalData->temperature);
            DEBUG_PRINT(" °C, Humidity: ");
            DEBUG_PRINT(internalData->humidity);
            DEBUG_PRINTLN(" % RH");
            break;
        }
        case Config::I2CSensorType::None:
            DEBUG_PRINTLN("No sensor type selected for this I2C address in config!");
            break;
        default:
            DEBUG_PRINTLN("Unknown sensor type, cannot validate.");
            break;
        }

        // if (!sensorManager.updateAll())
        // {
        //     DEBUG_PRINTLN("Sensor Manager update failed.");
        // }
        // DEBUG_PRINTLN("Sensor Manager update successful.");
        // if (!sensorManager.i2cSensors[0]->isValid())
        // {
        //     DEBUG_PRINTLN("BMP280 sensor is not valid.");
        //     continue;
        // }
        // dataBMP280 = sensorManager.i2cSensors[0]->getData();
        // DEBUG_PRINT("BMP280 Sensor Data: ");
        // DEBUG_PRINT("Temperature: ");
        // DEBUG_PRINT(dataBMP280->temperature);
        // DEBUG_PRINT(" °C, Pressure: ");
        // DEBUG_PRINT(dataBMP280->pressure);
        // DEBUG_PRINT(" hPa, Altitude: ");
        // DEBUG_PRINT(dataBMP280->altitude);
        // DEBUG_PRINTLN(" m");

        // DEBUG_PRINTLN("Loop iteration complete.");
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