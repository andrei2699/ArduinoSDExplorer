#include "CommandParser.h"

#include "UnknownCommand.h"

namespace commands
{
    ICommand* CommandParser::Parse(String string)
    {
        return new UnknownCommand();
    }
} // commands
