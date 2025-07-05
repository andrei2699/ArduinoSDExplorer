#include "SdCardController.h"

namespace sd
{
    bool SdCardController::initialize()
    {
        if (initializationType == NORMAL)
        {
            return true;
        }

        if (!sd.begin(config))
        {
            initializationType = NOT_INITIALIZED;
            return false;
        }

        initializationType = NORMAL;
        return true;
    }

    bool SdCardController::initialize_low_level()
    {
        if (initializationType == LOW_LEVEL)
        {
            return true;
        }

        if (!sd.cardBegin(config))
        {
            initializationType = NOT_INITIALIZED;
            return false;
        }

        initializationType = LOW_LEVEL;
        return true;
    }

    void SdCardController::print_error(const String& error) const
    {
        if (sd.sdErrorCode())
        {
            Serial.print("ERR ");
            Serial.print(error);
            Serial.print(" SYMBOL ");
            printSdErrorSymbol(&Serial, sd.sdErrorCode());
            Serial.print(" CODE ");
            Serial.print(static_cast<int>(sd.sdErrorCode()));
            Serial.print(" DATA ");
            Serial.println(static_cast<int>(sd.sdErrorData()));
        }
        else
        {
            Serial.print("ERR ");
            Serial.println(error);
        }
    }

    SdFs& SdCardController::getSdFs() const
    {
        return sd;
    }
} // sd
