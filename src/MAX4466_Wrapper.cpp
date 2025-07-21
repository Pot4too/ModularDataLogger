#include "MAX4466_Wrapper.h"

bool MAX4466_Wrapper::begin()
{
    isDataValid = isSensorPresent();
    DEBUG_PRINTLN("Is Analog Sensor data Valid? " + String(isDataValid));
    if (!isDataValid)
    {
        LOCAL_DEBUG_PRINTLN("MAX4466 sensor not present on pin " + String(pin));
        return false;
    }
    return true;
}

bool MAX4466_Wrapper::update()
{
    if (!isDataValid)
    {
        LOCAL_DEBUG_PRINTLN("MAX4466 sensor data is not valid, skipping update.");
        return false;
    }
    data = analogRead(pin);
    return true;
}

const void MAX4466_Wrapper::debugPrintData() const
{
    LOCAL_DEBUG_PRINT("MAX4466 Sensor Data: ");
    LOCAL_DEBUG_PRINT("Analog Value: ");
    LOCAL_DEBUG_PRINT(data);
    LOCAL_DEBUG_PRINTLN(" (raw)");
}

bool MAX4466_Wrapper::logDataToSd(File *dataFile)
{
    if (!isDataValid)
    {
        LOCAL_DEBUG_PRINTLN("MAX4466 sensor data is not valid, skipping logging.");
        dataFile->print("ERR");
        return false;
    }
    dataFile->print(data);
    return true;
}

void MAX4466_Wrapper::createNameHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    dataFile->print(getSensorName());
}

void MAX4466_Wrapper::createDataTypesHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    dataFile->print(namesOfData()[0]);
}
