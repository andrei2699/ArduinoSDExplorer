#ifndef COMMAND_H
#define COMMAND_H

#include "sd/SdCardController.h"

namespace commands
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void execute(sd::SdCardController& sdCard) = 0;

    protected:
        static bool init(sd::SdCardController& sdCard);
        static bool init_low_level(sd::SdCardController& sdCard);
    };
}

#endif //COMMAND_H
