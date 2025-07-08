#pragma once
#include "config.h"
#include <SD.h>
#include <FS.h>
#include <SPI.h>
#include <string.h>

class GenericSensorLogger
{
public:
    virtual bool logDataToSd(File *dataFile);
    virtual void createNameHeader(File *dataFile);
    virtual void createDataTypesHeader(File *dataFile);

protected:
    virtual const uint8_t numberOfUniqueData() const = 0;
    virtual const char *const *namesOfData() const = 0;
};

class DataLogger
{
public:
    DataLogger(SPIClass &mainSPI)
    {
        internalSPI = mainSPI;
    }
    bool begin();
    void endRow();
    const void debugPrintCardInfo() const;
    File *openFile();
    const bool isFileOpen() const
    {
        return fileIsOpen;
    }
    void addRowID() { dataRowID++; }
    void writeRowID(File *dataFile)
    {
        dataFile->print(dataRowID);
        dataFile->print(",");
    }
    void nextLine();

private:
    bool createNewLogFile(uint16_t index);
    uint16_t determineNewLogIndex();
    String filePath;
    SPIClass internalSPI;
    File dataFile;
    bool fileIsOpen = false;
    uint32_t dataRowID = 0;

    String baseName = "/log_";
    String fileExtension = ".csv";
};