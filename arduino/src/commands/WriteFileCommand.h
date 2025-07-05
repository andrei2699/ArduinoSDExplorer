#ifndef WRITEFILECOMMAND_H
#define WRITEFILECOMMAND_H
#include "ICommand.h"

namespace commands
{
    class WriteFileCommand final : public ICommand
    {
    public:
        void execute(sd::SdCardController& sdCard) override;
    };
} // commands

#endif //WRITEFILECOMMAND_H
