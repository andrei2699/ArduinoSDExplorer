#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include "ICommand.h"

namespace commands
{
    class UnknownCommand final : public ICommand
    {
    public:
        void execute() override;
    };
} // commands

#endif //UNKNOWNCOMMAND_H
