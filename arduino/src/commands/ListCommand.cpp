#include "ListCommand.h"
#include <Arduino.h>
// #include <SD.h>

namespace commands
{
    void ListCommand::execute(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize())
        {
            return;
        }

        sdCard.getSdFs().ls("/", LS_R);

        Serial.println("OK END");
    }


    // void ListCommand::printDirectory(SDLib::File dir, int numTabs)
    // {
    //     while (true)
    //     {
    //         SDLib::File entry = dir.openNextFile();
    //         if (!entry)
    //         {
    //             // no more files
    //             break;
    //         }
    //         for (uint8_t i = 0; i < numTabs; i++)
    //         {
    //             Serial.print('\t');
    //         }
    //         Serial.print(entry.name());
    //         if (entry.isDirectory())
    //         {
    //             Serial.println("/");
    //             printDirectory(entry, numTabs + 1);
    //         }
    //         else
    //         {
    //             // files have sizes, directories do not
    //             Serial.print("\t\t");
    //             Serial.println(entry.size(), DEC);
    //         }
    //         entry.close();
    //     }
    // }
} // commands
