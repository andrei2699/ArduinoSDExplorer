#ifndef INFOCOMMAND_H
#define INFOCOMMAND_H

#include "ICommand.h"

namespace commands
{
    class InfoCommand final : public ICommand
    {
    public:
        void execute(SdSpiConfig config, SdFs& sd) override;

    private:
        static void print_card_type(SdFs& sd);
        static void print_speed_type(SdFs& sd);
        static void print_cid();
        static void print_csd();
        static void print_ocr();
        static bool print_master_boot_record(SdFs& sd);
        static bool print_volume(SdFs& sd);

        static bool retry_operation(bool (*function)(SdFs& sd), SdFs& sd, const int retries = 3)
        {
            for (int i = 0; i < retries; ++i)
            {
                if (function(sd))
                {
                    return true;
                }
                Serial.println("retrying...");
                delay(1000);
            }
            return false;
        }
    };
} // commands


#endif //INFOCOMMAND_H
