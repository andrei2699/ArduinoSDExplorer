#ifndef SDCARD_H
#define SDCARD_H

#include "SdCardInitializationType.h"
#include "SdFat.h"

namespace sd
{
    class SdCardController
    {
    public:
        SdCardController(const SdSpiConfig& config, SdFs& sd):
            config(config), sd(sd)
        {
        }

        bool initialize();
        bool initialize_low_level();
        void print_error(const String& error) const;
        SdFs& getSdFs() const;

    private:
        const SdSpiConfig config;
        SdFs& sd;
        SdCardInitializationType initializationType = NOT_INITIALIZED;
    };
} // sd

#endif //SDCARD_H
