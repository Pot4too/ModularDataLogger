#include "dataLogger.h"

bool DataLogger::begin()
{
    delay(100);
    if (!SD.begin(Config::SD_CS_PIN, internalSPI))
    {
        DEBUG_PRINTLN("SD card initialization failed!");
        return false;
    }
    if (!createNewLogFile(determineNewLogIndex()))
    {
        DEBUG_PRINTLN("SD Card failed to create a new Log file!");
        return false;
    }
    DEBUG_PRINTLN("SD card initialized successfully.");
    debugPrintCardInfo();
    DEBUG_PRINTLN("New log file created: " + filePath);
    return true;
}

bool DataLogger::createNewLogFile(uint16_t index)
{
    filePath = baseName + String(index) + fileExtension;
    File file = SD.open(filePath, FILE_WRITE);
    if (!file)
    {
        DEBUG_PRINTLN("SD card failed to create a new log file");
        return false;
    }
    file.close();
    return true;
}

File *DataLogger::openFile()
{
    if (isFileOpen())
        return &dataFile;
    dataFile = SD.open(filePath, FILE_APPEND);
    fileIsOpen = true;
    return &dataFile;
}

uint16_t DataLogger::determineNewLogIndex()
{
    String filename;
    uint16_t fileIndex = 0;
    do
    {
        filename = baseName + String(fileIndex++) + fileExtension;
    } while (SD.exists(filename));
    return fileIndex - 1;
}

void DataLogger::endRow()
{
    File file = *openFile();
    file.println();
    file.close();
    fileIsOpen = false;
}

void DataLogger::nextLine()
{
    File file = *openFile();
    file.println();
}

const void DataLogger::debugPrintCardInfo() const
{
    DEBUG_PRINTLN("SD Card Info:");
    DEBUG_PRINTLN("Card Type: " + String(SD.cardType()));
    DEBUG_PRINTLN("Card Size: " + String(SD.cardSize() / (1024 * 1024)) + " MB");
    // DEBUG_PRINTLN("Volume Size: " + String(SD.volumeSize() / (1024 * 1024)) + " MB");
    DEBUG_PRINTLN("Total Bytes: " + String(SD.totalBytes()));
    DEBUG_PRINTLN("Used Bytes: " + String(SD.usedBytes()));
}