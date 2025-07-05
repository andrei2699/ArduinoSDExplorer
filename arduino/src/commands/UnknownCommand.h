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

        void execute(sd::SdCardController& sdCard) override;

    private:
        String command;
    };
} // commands

#endif //UNKNOWNCOMMAND_H
