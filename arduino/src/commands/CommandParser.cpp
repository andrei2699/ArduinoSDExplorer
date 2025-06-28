#include "CommandParser.h"

#include "InfoCommand.h"
#include "UnknownCommand.h"

namespace commands
{
    ICommand* CommandParser::Parse(String command)
    {
        command.toUpperCase();

        if (command.equals("INFO"))
        {
            return new InfoCommand();
        }

        return new UnknownCommand();
    }
} // commands
