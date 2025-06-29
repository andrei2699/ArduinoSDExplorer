#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

inline void hexDump(const void* data, size_t size)
{
    const auto bytes = static_cast<const uint8_t*>(data);
    for (size_t i = 0; i < size; ++i)
    {
        if (bytes[i] < 0x10)
        {
            Serial.print('0');
        }
        Serial.print(bytes[i], HEX);
    }
    Serial.println();
}

#endif //UTILS_H
