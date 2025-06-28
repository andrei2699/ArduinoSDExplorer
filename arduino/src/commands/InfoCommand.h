#ifndef INFOCOMMAND_H
#define INFOCOMMAND_H

#include "ICommand.h"
#include "utility/Sd2Card.h"
#include "utility/SdFat.h"

namespace commands
{
    class InfoCommand final : public ICommand
    {
    public:
        void execute() override;

    private:
        static void print_card_type(const Sd2Card& card);
        static void print_volume_info(const SdVolume& volume);
        static void print_files(SdVolume volume);
    };
} // commands


#endif //INFOCOMMAND_H
