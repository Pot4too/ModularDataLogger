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
#include <Adafruit_MAX4466.h>

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