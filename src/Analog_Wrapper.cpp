// #include <Analog_Wrapper.h>

// /**
//  * @brief Initializes the analog sensor based on its type.
//  *
//  * @return true if the sensor voltage reading is above threshold, false otherwise.
//  */
// bool Analog_Wrapper::initialize()
// {
//     float voltage = NAN;
//     switch (type)
//     {
//     case CapacitiveMoisture:
//         pinMode(pin, PULLDOWN);
//         delay(10);                                  // Set pin as input with pull-down resistor
//         voltage = analogRead(pin) * (3.3 / 4095.0); // Read voltage from the pin
//         if (voltage < 0.1)
//             initialized = false; // If so, mark as not initialized
//         else
//             initialized = true; // Otherwise, mark as initialized
//         return initialized;
//     case MAX4466: // Microphone sensor
//         pinMode(pin, PULLDOWN);
//         delay(10);                                  // Set pin as input with pull-down resistor
//         voltage = analogRead(pin) * (3.3 / 4095.0); // Read voltage from the pin
//         if (voltage < 0.1)
//             initialized = false; // If so, mark as not initialized
//         else
//             initialized = true; // Otherwise, mark as initialized
//         return initialized;
//     default:
//         DEBUG_PRINTLN("Unknown analog sensor type, using generic initialization.");
//         pinMode(pin, PULLDOWN);
//         delay(10);                                  // Set pin as input with pull-down resistor
//         voltage = analogRead(pin) * (3.3 / 4095.0); // Read voltage from the pin
//         if (voltage < 0.1)
//             initialized = false; // If so, mark as not initialized
//         else
//             initialized = true; // Otherwise, mark as initialized
//         return initialized;
//     }
// }

// /**
//  * @brief Reads the value from the analog sensor.
//  *
//  * @return The voltage reading from the sensor.
//  */
// float Analog_Wrapper::readValue()
// {
//     if (!initialized)
//     {
//         DEBUG_PRINTLN("Analog sensor not initialized. Please call initialize() first.");
//         return NAN; // Return NaN if the sensor is not initialized
//     }
//     return analogRead(pin);
// }