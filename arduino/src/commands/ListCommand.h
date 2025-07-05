#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H

#include "ICommand.h"
// #include "SD.h"

namespace commands
{
    class ListCommand final : public ICommand
    {
    public:
        void execute(sd::SdCardController& sdCard) override;

    private:
        // static void printDirectory(SDLib::File dir, int numTabs);
    };
} // commands

#endif //LISTCOMMAND_H
