#pragma once
#include "config.h"
#include <SD.h>
#include <SPI.h>

class GenericSensorLogger
{
public:
    virtual bool logDataToSd(File *dataFile);

protected:
};

class DataLogger
{
public:
    DataLogger(SPIClass &mainSPI)
    {
        internalSPI = mainSPI;
    }
    bool begin();
    bool createNewLogFile(uint16_t index);
    void createHeader();
    File *getDataFile()
    {
        return &dataFile;
    }
    void debugPrintCardInfo() const;
    File *openFile();
    const bool isFileOpen() const
    {
        return &fileIsOpen;
    }

private:
    uint16_t determineNewLogIndex();
    string filePath;
    SPIClass *internalSPI;
    // File dataFile;
    bool fileIsOpen = false;
};