#ifndef INFOCOMMAND_H
#define INFOCOMMAND_H

#include "ICommand.h"

namespace commands
{
    class InfoCommand final : public ICommand
    {
    public:
        void execute(sd::SdCardController& sdCard) override;

    private:
        static void print_card_type(SdFs& sd);
        static void print_speed_type(SdFs& sd);
        static void print_cid();
        static void print_csd();
        static void print_ocr();
        static bool print_master_boot_record(SdFs& sd);
        static bool print_volume(SdFs& sd);
    };
} // commands


#endif //INFOCOMMAND_H
