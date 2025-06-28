#ifndef COMMAND_H
#define COMMAND_H

namespace commands
{
    class ICommand
    {
    public:
        virtual ~ICommand()
        {
        }

        virtual void execute() = 0;
    };
}

#endif //COMMAND_H
