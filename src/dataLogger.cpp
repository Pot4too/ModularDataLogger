#include "dataLogger.h"

bool DataLogger::begin()
{
    if (SD.begin(Config::SD_CS_PIN, internalSPI, Config::SPI_Frequency))
    {
        DEBUG_PRINTLN("SD card initialization failed!");
        return false;
        if (createNewLogFile(determineNewLogIndex()))
        {
            DEBUG_PRINTLN("SD Card failed to create a new Log file!");
            return false;
        }
        createHeader();
        return true;
    }
}

void DataLogger::debugPrintCardInfo()
{
    DEBUG_PRINTLN("SD Card Info:");
    DEBUG_PRINTLN("Card Type: " + String(SD.cardType()));
    DEBUG_PRINTLN("Card Size: " + String(SD.cardSize() / (1024 * 1024)) + " MB");
    DEBUG_PRINTLN("Volume Size: " + String(SD.volumeSize() / (1024 * 1024)) + " MB");
    DEBUG_PRINTLN("Total Blocks: " + String(SD.totalBlocks()));
    DEBUG_PRINTLN("Used Blocks: " + String(SD.usedBlocks()));
}