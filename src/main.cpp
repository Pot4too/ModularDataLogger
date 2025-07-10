#include "config.h"
#include "SensorManager.h"

SensorManager sensorManager;

uint64_t previousTime = 0;

void setup()
{
    Serial.begin(Config::SERIAL_BAUD_RATE);
    while (!Serial)
    {
        ;
    }

    DEBUG_PRINTLN("DEBUG MODE IS ENABLED");
    DEBUG_PRINTLN("Starting Sensor Manager...");

    if (!sensorManager.beginAll())
    {
        DEBUG_PRINTLN("Sensor Manager initialization failed.");
        return;
    }

    DEBUG_PRINTLN("Sensor Manager initialized successfully.");
}

void loop()
{
    if (millis() > previousTime + Config::LOOP_DELAY_MS)
    {
        if (!sensorManager.updateAll())
        {
            DEBUG_PRINTLN("Sensor Manager update failed.");
            return;
        }
        sensorManager.testI2CSensors();
        if (!sensorManager.logSensorsDataToSd())
        {
            DEBUG_PRINTLN("Failed to log sensor data to SD card.");
        }
        else
        {
            DEBUG_PRINTLN("Sensor data logged successfully.");
        }
        previousTime = millis();
    }
}
