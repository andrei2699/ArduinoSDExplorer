#ifndef UNKNOWNCOMMAND_H
#define UNKNOWNCOMMAND_H

#include "ICommand.h"

namespace commands
{
    class UnknownCommand final : public ICommand
    {
    public:
        explicit UnknownCommand(const String& command): command(command)
        {
        }

        void execute(SdSpiConfig config, SdFs& sd) override;

    private:
        String command;
    };
} // commands

#endif //UNKNOWNCOMMAND_H
