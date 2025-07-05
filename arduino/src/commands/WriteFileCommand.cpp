#include "WriteFileCommand.h"

namespace commands
{
    void WriteFileCommand::execute(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize())
        {
            return;
        }

        FsFile myFile = sdCard.getSdFs().open("test.txt", FILE_WRITE);

        if (myFile)
        {
            Serial.print("Writing to test.txt...");
            myFile.println("testing 1, 2, 3.");

            myFile.close();
            Serial.println("done.");
        }
        else
        {
            Serial.println("error opening test.txt");
            sdCard.print_error("WriteFileFailed");
        }
    }
} // commands
