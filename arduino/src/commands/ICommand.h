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
    };
}

#endif //COMMAND_H
