#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <Arduino.h>
#include "ICommand.h"

namespace commands
{
    class CommandParser
    {
    public :
        static ICommand* Parse(String string);
    };
} // commands

#endif //COMMANDPARSER_H
