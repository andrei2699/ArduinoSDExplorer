#include "ICommand.h"

namespace commands
{
    bool ICommand::init(const SdSpiConfig& config, SdFs& sd)
    {
        if (!sd.begin(config))
        {
            print_error(sd, "SDInitFailed");
            return false;
        }
        return true;
    }

    bool ICommand::init_low_level(const SdSpiConfig& config, SdFs& sd)
    {
        if (!sd.cardBegin(config))
        {
            print_error(sd, "SDInitFailed");
            return false;
        }
        return true;
    }

    void ICommand::print_error(SdFs& sd, const String& error)
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
} // commands
