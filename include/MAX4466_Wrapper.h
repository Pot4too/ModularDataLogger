/**
 * @file MAX4466_Wrapper.h
 * @author Potato
 * @brief Wrapper for MAX4466 microphone sensor
 * @details This file contains the MAX4466_Wrapper class, which provides an interface for
 *          interacting with the MAX4466 microphone sensor. It inherits from GenericAnalogSensorBase
 *          and implements methods for initialization, data retrieval, and logging to SD card.
 * @version 0.1
 * @date 2025-07-10
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

//! Includes
#include <config.h>
#include <GenericSensorBase.h>

// Local debug flag to enable/disable debug prints
// #define LOCAL_DEBUG

// Debug print macros
#if defined(LOCAL_DEBUG) || defined(GLOBAL_DEBUG_OVERRIDE)
#define LOCAL_DEBUG_PRINT(x) DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x) DEBUG_PRINTLN(x)
#else
#define LOCAL_DEBUG_PRINT(x)
#define LOCAL_DEBUG_PRINTLN(x)
#endif // DEBUG

class MAX4466_Wrapper : public GenericAnalogSensorBase
{
public:
    MAX4466_Wrapper(uint8_t _pin) { pin = _pin; }

    bool begin() override;
    bool update() override;

    const char *getSensorName() const override { return "MAX4466"; }
    const void *getData() const override { return &data; }
    Config::AnalogSensorType getSensorType() const override { return Config::AnalogSensorType::MAX4466; }

    bool logDataToSd(File *dataFile) override;
    void createNameHeader(File *dataFile) override;
    void createDataTypesHeader(File *dataFile) override;

    const void debugPrintData() const override;

private:
    static constexpr const char *FIELD_NAMES[] = {"Analog Sound"};
    const uint8_t numberOfUniqueData() const override { return sizeof(FIELD_NAMES) / sizeof(FIELD_NAMES[0]); }
    const char *const *namesOfData() const override { return FIELD_NAMES; }
};
