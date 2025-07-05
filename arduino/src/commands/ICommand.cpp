#include "ICommand.h"

#include "sd/SdCardController.h"

namespace commands
{
    bool ICommand::init(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize())
        {
            sdCard.print_error("SDInitFailed");
            return false;
        }
        return true;
    }

    bool ICommand::init_low_level(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize_low_level())
        {
            sdCard.print_error("SDInitFailed");
            return false;
        }
        return true;
    }
} // commands
