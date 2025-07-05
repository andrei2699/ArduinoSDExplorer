#include "UnknownCommand.h"
#include <Arduino.h>

namespace commands
{
    void UnknownCommand::execute(sd::SdCardController& sdCard)
    {
        Serial.print("ERR UnknownCommand ");
        Serial.println(command);
    }
} // commands
