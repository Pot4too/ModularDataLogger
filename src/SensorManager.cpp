#include "SensorManager.h"

bool SensorManager::beginAll()
{
    if (!mainWire->begin(Config::I2C_SDA_PIN, Config::I2C_SCL_PIN))
    {
        DEBUG_PRINTLN("Failed to initialize I2C Wire.");
        return false;
    }
    DEBUG_PRINTLN("I2C Wire initialized successfully.");

    beginSPI();

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

    if (beginDataLogger())
        createLogFileHeader();

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
    for (uint8_t i = 8; i < 120; i++)
    {
        mainWire->beginTransmission(i);
        if (!mainWire->endTransmission() == 0)
        {
            DEBUG_PRINTLN("No device found at address 0x" + String(i, HEX));
            continue;
        }
        DEBUG_PRINTLN("Device found at address 0x" + String(i, HEX) + ", initializing sensor... ");
        for (uint8_t j = 0; j < Config::numberOfKnownI2CSensors; j++)
        {
            if (i != Config::I2CSensorTable[j].address)
                continue;
            i2cSensors[numberOfInitializedI2CSensors] = createI2CSensorInstance(Config::I2CSensorTable[j].type, Config::I2CSensorTable[j].address);
            if (i2cSensors[numberOfInitializedI2CSensors] == nullptr)
            {
                DEBUG_PRINTLN("Failed to create sensor instance for address 0x" + String(i, HEX));
                continue;
            }
            DEBUG_PRINTLN("Sensor instance created for " + String(i2cSensors[numberOfInitializedI2CSensors]->getSensorName()) + " at address 0x" + String(i, HEX));
            if (!i2cSensors[numberOfInitializedI2CSensors]->begin())
            {
                DEBUG_PRINTLN("Failed to initialize sensor at address 0x" + String(i, HEX));
                delete i2cSensors[numberOfInitializedI2CSensors];
                i2cSensors[numberOfInitializedI2CSensors] = nullptr;
                continue;
            }
            numberOfInitializedI2CSensors++;
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
    DEBUG_PRINTLN("Starting Analog sensors initialization.");
    for (uint8_t i = 0; i < Config::AnalogSensorCount; i++)
    {
        if (Config::AnalogSensorTable[i].type == Config::AnalogSensorType::None)
            continue;
        analogSensors[numberOfInitializedAnalogSensors] = createAnalogSensorInstance(Config::AnalogSensorTable[i].type, Config::AnalogSensorTable[i].pin);
        if (analogSensors[numberOfInitializedAnalogSensors] == nullptr)
        {
            DEBUG_PRINTLN("Failed to create analog sensor instance for pin " + String(Config::AnalogSensorTable[i].pin));
            continue;
        }
        if (!analogSensors[numberOfInitializedAnalogSensors]->begin())
        {
            DEBUG_PRINTLN("Failed to initialize analog sensor on pin " + String(Config::AnalogSensorTable[i].pin));
            delete analogSensors[numberOfInitializedAnalogSensors];
            analogSensors[numberOfInitializedAnalogSensors] = nullptr;
            continue;
        }
        DEBUG_PRINTLN("Analog sensor initialized on pin " + String(Config::AnalogSensorTable[i].pin));
        numberOfInitializedAnalogSensors++;
    }
    return true;
}

bool SensorManager::updateAnalogSensors()
{
    for (uint8_t i = 0; i < numberOfInitializedAnalogSensors; i++)
    {
        if (analogSensors[i] == nullptr)
            continue;
        if (!analogSensors[i]->update())
        {
            DEBUG_PRINTLN("Failed to update analog sensor: " + String(analogSensors[i]->getSensorName()));
            continue;
        }
    }
    return true;
}

GenericI2CSensorBase *SensorManager::createI2CSensorInstance(Config::I2CSensorType type, uint8_t i2cAddress)
{
    switch (type)
    {
    case Config::I2CSensorType::BMP280:
        return new BMP280_Wrapper(i2cAddress, *mainWire);
        break;
    case Config::I2CSensorType::AHT20:
        return new AHT20_Wrapper(i2cAddress, *mainWire);
        break;
    case Config::I2CSensorType::MPU6050:
        return new MPU6050_Wrapper(i2cAddress, *mainWire);
        break;
    case Config::I2CSensorType::None:
        DEBUG_PRINTLN("No sensor type defined for this address, skipping initialization.");
        break;
    default:
        DEBUG_PRINTLN("Unknown I2C sensor type, cannot create instance.");
        return nullptr;
    }
    return nullptr;
}

void SensorManager::beginSPI()
{
    mainSPI.begin(Config::SPI_SCK_PIN, Config::SPI_MISO_PIN, Config::SPI_MOSI_PIN);
    // mainSPI.beginTransaction(SPISettings(Config::SPI_Frequency, MSBFIRST, SPI_MODE0));
    //  mainSPI = &SPI;
    DEBUG_PRINTLN("SPI initialized successfully.");
    return;
}
bool SensorManager::beginDataLogger()
{
    dataLogger = new DataLogger(mainSPI);
    if (dataLogger == nullptr)
    {
        DEBUG_PRINTLN("Failed to create Data Logger instance.");
        dataLoggerInitialized = false;
        return false;
    }
    if (!dataLogger->begin())
    {
        DEBUG_PRINTLN("Failed to initialize Data Logger.");
        dataLoggerInitialized = false;
        return false;
    }
    dataLoggerInitialized = true;
    DEBUG_PRINTLN("Data Logger initialized successfully.");
    return true;
}

bool SensorManager::logSensorsDataToSd()
{
    if (!dataLoggerInitialized)
    {
        DEBUG_PRINTLN("Data Logger is not initialized, cannot log data.");
        return false;
    }
    File *dataFile = dataLogger->openFile();
    if (dataFile == nullptr)
    {
        DEBUG_PRINTLN("Failed to open data file for logging.");
        return false;
    }

    dataLogger->writeRowID(dataFile);
    // Log I2C Sensors data
    for (uint8_t i = 0; i < numberOfInitializedI2CSensors; i++)
    {
        if (i2cSensors[i] == nullptr)
            continue;
        if (!i2cSensors[i]->logDataToSd(dataFile))
        {
            DEBUG_PRINTLN("Failed to log data for sensor: " + String(i2cSensors[i]->getSensorName()));
            continue;
        }
        if (i != numberOfInitializedI2CSensors - 1)
            dataFile->print(",");
    }

    dataFile->print(",");

    // Log Analog sensors data
    for (int i = 0; i < AnalogSensorCount; i++)
    {
        if (analogSensors[i] == nullptr)
            continue;
        if (!analogSensors[i]->logDataToSd(dataFile))
        {
            DEBUG_PRINTLN("Failed to log data for sensor: " + String(analogSensors[i]->getSensorName()));
            continue;
        }
        if (i != AnalogSensorCount - 1)
            dataFile->print(",");
    }
    dataLogger->endRow();
    dataLogger->addRowID(); // rowID++
    return true;
}

void SensorManager::createLogFileHeader()
{
    File *dataFile = dataLogger->openFile();
    if (dataFile == nullptr)
    {
        DEBUG_PRINTLN("Failed to open data file for logging.");
        return;
    }
    dataFile->print("Timestamp,");

    // Create a Sensor type header I2C sensors
    for (uint8_t i = 0; i < numberOfInitializedI2CSensors; i++)
    {
        if (i2cSensors[i] == nullptr)
            continue;
        i2cSensors[i]->createNameHeader(dataFile);
        if (i != numberOfInitializedI2CSensors - 1)
            dataFile->print(",");
    }
    dataFile->print(",");
    // Create a sensor type header Analog sensors
    for (uint8_t i = 0; i < AnalogSensorCount; i++)
    {
        if (analogSensors[i] == nullptr)
            continue;
        analogSensors[i]->createNameHeader(dataFile);
        if (i != AnalogSensorCount)
            dataFile->print(",");
    }
    dataLogger->nextLine();
    dataFile->print("ID,");

    // Data type header for I2C sensors
    for (uint8_t i = 0; i < numberOfInitializedI2CSensors; i++)
    {
        if (i2cSensors[i] == nullptr)
            continue;
        i2cSensors[i]->createDataTypesHeader(dataFile);
        if (i != numberOfInitializedI2CSensors - 1)
            dataFile->print(",");
    }

    // Data type header for analog sensors
    for (uint8_t i = 0; i < AnalogSensorCount; i++)
    {
        if (analogSensors[i] == nullptr)
            continue;
        analogSensors[i]->createDataTypesHeader(dataFile);
        if (i != AnalogSensorCount)
            dataFile->print(",");
    }
    dataLogger->endRow();
}

GenericAnalogSensorBase *SensorManager::createAnalogSensorInstance(Config::AnalogSensorType _type, uint8_t _pin)
{
    switch (_type)
    {
    case Config::AnalogSensorType::MAX4466:
        return new MAX4466_Wrapper(_pin);
        break;
    case Config::AnalogSensorType::CapacitiveMoisture:
        DEBUG_PRINTLN("Capacitive Moisture sensor is not implemented yet.");
        return nullptr;
    case Config::AnalogSensorType::MQ135:
        DEBUG_PRINTLN("MQ135 sensor is not implemented yet.");
        return nullptr;
    case Config::AnalogSensorType::Generic:
        DEBUG_PRINTLN("Generic analog sensor is not implemented yet.");
        return nullptr;
    default:
        DEBUG_PRINTLN("Unknown analog sensor type, cannot create instance.");
        return nullptr;
    }
    return nullptr;
}