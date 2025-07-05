#include "CommandParser.h"

#include "InfoCommand.h"
#include "ListCommand.h"
#include "UnknownCommand.h"
#include "WriteFileCommand.h"

namespace commands
{
    ICommand* CommandParser::Parse(String command)
    {
        command.toUpperCase();

        if (command.equals("INFO"))
        {
            return new InfoCommand();
        }

        if (command.equals("LIST"))
        {
            return new ListCommand();
        }

        if (command.equals("WRITE"))
        {
            return new WriteFileCommand();
        }

        return new UnknownCommand(command);
    }
} // commands
