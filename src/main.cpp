#include "config.h"
#include "SensorManager.h"
// #include "BMP280_Wrapper.h"

SensorManager sensorManager;
// Data *dataBMP280;
// BMP280_Wrapper::Data testingData;

void setup()
{
    Serial.begin(Config::SERIAL_BAUD_RATE);
    while (!Serial)
        ; // Wait for serial port to connect. Needed for native USB port only

    DEBUG_PRINTLN("DEBUG MODE IS ENABLED");
    DEBUG_PRINTLN("Starting Sensor Manager...");

    if (!sensorManager.beginAll())
    {
        DEBUG_PRINTLN("Sensor Manager initialization failed.");
        return;
    }

    DEBUG_PRINTLN("Sensor Manager initialized successfully.");
    sensorManager.updateAll();
    // DEBUG_PRINTLN(testingData.temperature);
}

void loop()
{
    delay(3000);
    if (!sensorManager.updateAll())
    {
        DEBUG_PRINTLN("Sensor Manager update failed.");
        return;
    }
    sensorManager.testBMP280();
}
