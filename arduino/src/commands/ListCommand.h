#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H

#include "ICommand.h"

namespace commands
{
    class ListCommand final : public ICommand
    {
    public:
        void execute(sd::SdCardController& sdCard) override;
    };
} // commands

#endif //LISTCOMMAND_H
