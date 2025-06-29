#include "ListCommand.h"
#include "SdFat.h"

namespace commands
{
    void ListCommand::execute(const SdSpiConfig config, SdFs& sd)
    {
        if (!init(config, sd))
        {
            return;
        }

        Serial.println("OK END");
    }
} // commands
