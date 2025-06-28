#include "InfoCommand.h"

#include <Arduino.h>
#include <SD.h>


namespace commands
{
    void InfoCommand::execute()
    {
        Sd2Card card;
        SdVolume volume;

        print_card_type(card);

        if (!volume.init(card))
        {
            Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
            Serial.println("OK END");
            return;
        }

        print_volume_info(volume);

        print_files(volume);

        Serial.println("OK END");
    }

    void InfoCommand::print_card_type(const Sd2Card& card)
    {
        Serial.print("Card type: ");

        switch (card.type())
        {
        case SD_CARD_TYPE_SD1:
            Serial.println("SD1");
            break;
        case SD_CARD_TYPE_SD2:
            Serial.println("SD2");
            break;
        case SD_CARD_TYPE_SDHC:
            Serial.println("SDHC");
            break;
        default:
            Serial.println("Unknown");
        }
    }

    void InfoCommand::print_volume_info(const SdVolume& volume)
    {
        Serial.print("Clusters: ");
        Serial.println(volume.clusterCount());

        Serial.print("Blocks x Cluster: ");
        Serial.println(volume.blocksPerCluster());

        Serial.print("Total Blocks: ");
        Serial.println(volume.blocksPerCluster() * volume.clusterCount());
        Serial.println();

        Serial.print("Volume type is: FAT");
        Serial.println(volume.fatType(), DEC);

        uint32_t volume_size = volume.blocksPerCluster();
        volume_size *= volume.clusterCount();
        volume_size /= 2;

        Serial.print("Volume size (Kb):  ");
        Serial.println(volume_size);

        Serial.print("Volume size (Mb):  ");
        volume_size /= 1024;
        Serial.println(volume_size);

        Serial.print("Volume size (Gb):  ");
        Serial.println(static_cast<float>(volume_size) / 1024.0);
    }

    void InfoCommand::print_files(SdVolume volume)
    {
        Serial.println();
        Serial.println("Files found on the card (name, date and size in bytes): ");

        SdFile root;

        root.openRoot(volume);
        root.ls(LS_R | LS_DATE | LS_SIZE);
        root.close();
    }
} // commands
