#include <MPU6050_Wrapper.h>

MPU6050_Wrapper::MPU6050_Wrapper(uint8_t _address, TwoWire &_wire)
{
    i2cAddress = _address;
    wire = &_wire;
}

bool MPU6050_Wrapper::begin()
{
    if (!sensor.begin(i2cAddress, wire, sensorID))
        return false;
    setSenosorConfiguration();
    return true;
}

bool MPU6050_Wrapper::update()
{
    sensors_event_t _acceleration, _rotation, _temperature;
    if (!sensor.getEvent(&_acceleration, &_rotation, &_temperature))
        return false;
    isValid_Bool = true;
    data.aX = _acceleration.acceleration.x;
    data.aY = _acceleration.acceleration.y;
    data.aZ = _acceleration.acceleration.z;
    data.gX = _rotation.gyro.x;
    data.gY = _rotation.gyro.y;
    data.gZ = _rotation.gyro.z;
    data.temperature = _temperature.temperature;
    return true;
}

const void MPU6050_Wrapper::debugPrintData() const
{
    LOCAL_DEBUG_PRINT("MPU6050 Sensor Data: ");
    LOCAL_DEBUG_PRINT("Acceleration: ");
    LOCAL_DEBUG_PRINT("X: ");
    LOCAL_DEBUG_PRINT(data.aX);
    LOCAL_DEBUG_PRINT(", Y: ");
    LOCAL_DEBUG_PRINT(data.aY);
    LOCAL_DEBUG_PRINT(", Z: ");
    LOCAL_DEBUG_PRINT(data.aZ);
    LOCAL_DEBUG_PRINT(" m/s^2, Angular Velocity: ");
    LOCAL_DEBUG_PRINT("X: ");
    LOCAL_DEBUG_PRINT(data.gX);
    LOCAL_DEBUG_PRINT(", Y: ");
    LOCAL_DEBUG_PRINT(data.gY);
    LOCAL_DEBUG_PRINT(", Z: ");
    LOCAL_DEBUG_PRINT(data.gZ);
    LOCAL_DEBUG_PRINT(" rad/s, Temperature: ");
    LOCAL_DEBUG_PRINT(data.temperature);
    LOCAL_DEBUG_PRINTLN(" °C");
}

bool MPU6050_Wrapper::logDataToSd(File *dataFile)
{
    if (!isValid())
    {
        LOCAL_DEBUG_PRINTLN("MPU6050 sensor data is not valid, skipping logging.");
        for (int i = 0; i < numberOfUniqueData(); i++)
        {
            dataFile->print("ERR");
            if (i != numberOfUniqueData() - 1)
                dataFile->print(",");
        }
        return false;
    }

    dataFile->print(data.aX);
    dataFile->print(",");
    dataFile->print(data.aY);
    dataFile->print(",");
    dataFile->print(data.aZ);
    dataFile->print(",");
    dataFile->print(data.gX);
    dataFile->print(",");
    dataFile->print(data.gY);
    dataFile->print(",");
    dataFile->print(data.gZ);
    dataFile->print(",");
    dataFile->println(data.temperature);
    return true;
}

void MPU6050_Wrapper::createNameHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating name header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        dataFile->print(getSensorName());
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void MPU6050_Wrapper::createDataTypesHeader(File *dataFile)
{
    LOCAL_DEBUG_PRINTLN("Creating data type header for " + String(getSensorName()) + " sensor.");
    for (int i = 0; i < int(numberOfUniqueData()); i++)
    {
        dataFile->print(namesOfData()[i]);
        if (i != numberOfUniqueData() - 1)
            dataFile->print(",");
    }
}

void MPU6050_Wrapper::setSenosorConfiguration()
{
    sensor.setAccelerometerRange(MPU6050_RANGE_8_G);
    sensor.setGyroRange(MPU6050_RANGE_500_DEG);
    sensor.setFilterBandwidth(MPU6050_BAND_21_HZ);
}
