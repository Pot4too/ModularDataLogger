#pragma once
#include "config.h"
#include <SD.h>
#include <SPI.h>
#include <string.h>

class GenericSensorLogger
{
public:
    virtual bool logDataToSd(File *dataFile);
    virtual void createNameHeader(File *dataFile);
    virtual void createDataTypesHeader(File *dataFile);

protected:
    virtual const uint8_t numberOfUniqueData() const { return 0; }
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
    void endRow();
    const void debugPrintCardInfo() const;
    File *openFile();
    const bool isFileOpen() const
    {
        return fileIsOpen;
    }

private:
    uint16_t determineNewLogIndex();
    String filePath;
    SPIClass internalSPI;
    File dataFile;
    bool fileIsOpen = false;

    String baseName = "/log_";
    String fileExtension = ".csv";
};