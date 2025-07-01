#pragma once

class GenericSensorBase
{
public:
    virtual bool begin() = 0;
    virtual bool update() = 0;
    virtual const char *getSensorName() cosnt = 0;
    virtual const void *getData() const = 0;
    virtual bool isValid() const { return false; } // Default implementation, can be overridden
    virtual ~GenericSensorBase() {};
}
