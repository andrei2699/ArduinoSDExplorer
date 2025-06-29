#ifndef COMMAND_H
#define COMMAND_H

#include "SdFat.h"

namespace commands
{
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void execute(SdSpiConfig config, SdFs& sd) = 0;

    protected:
        static bool init(const SdSpiConfig& config, SdFs& sd);
        static bool init_low_level(const SdSpiConfig& config, SdFs& sd);
        static void print_error(SdFs& sd, const String& error);
    };
}

#endif //COMMAND_H
