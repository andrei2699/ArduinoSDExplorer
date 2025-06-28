#include "UnknownCommand.h"
#include <Arduino.h>

namespace commands
{
    void UnknownCommand::execute()
    {
        Serial.println("ERR UnknownCommand");
    }
} // commands
