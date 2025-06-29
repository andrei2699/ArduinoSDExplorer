#include "UnknownCommand.h"
#include <Arduino.h>

namespace commands
{
    void UnknownCommand::execute(SdSpiConfig config, SdFs& sd)
    {
        Serial.print("ERR UnknownCommand ");
        Serial.println(command);
    }
} // commands
