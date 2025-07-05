#include "ListCommand.h"
#include "SdFat.h"

namespace commands
{
    void ListCommand::execute(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize())
        {
            return;
        }

        Serial.println("OK END");
    }
} // commands
