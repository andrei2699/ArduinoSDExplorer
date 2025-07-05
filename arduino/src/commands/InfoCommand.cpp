#include "InfoCommand.h"
#include <Arduino.h>
#include "SdFat.h"
#include "utils.h"

cid_t cid;
csd_t csd;
scr_t scr;
uint32_t ocr;

uint8_t cmd6Data[64];

namespace commands
{
    void InfoCommand::execute(sd::SdCardController& sdCard)
    {
        if (!sdCard.initialize_low_level())
        {
            return;
        }

        SdFs& sd = sdCard.getSdFs();

        if (!sd.card()->readCID(&cid) || !sd.card()->readCSD(&csd) ||
            !sd.card()->readOCR(&ocr) || !sd.card()->readSCR(&scr))
        {
            sdCard.print_error("ReadInfoFailed");
            return;
        }

        print_card_type(sd);
        print_speed_type(sd);
        Serial.println();

        print_cid();
        Serial.println();

        print_csd();
        print_ocr();
        Serial.println();

        if (!print_master_boot_record(sd))
        {
            sdCard.print_error("ReadMBRFailed");
            return;
        }

        Serial.println();
        if (!print_volume(sd))
        {
            sdCard.print_error("ReadVolumeFailed");
            return;
        }

        Serial.println("OK END");
    }

    void InfoCommand::print_card_type(SdFs& sd)
    {
        Serial.print("Card type: ");

        switch (sd.card()->type())
        {
        case SD_CARD_TYPE_SD1:
            Serial.println("SD1");
            break;

        case SD_CARD_TYPE_SD2:
            Serial.println("SD2");
            break;

        case SD_CARD_TYPE_SDHC:
            if (csd.capacity() < 70000000)
            {
                Serial.println("SDHC");
            }
            else
            {
                Serial.println("SDXC");
            }
            break;

        default:
            Serial.println("Unknown");
        }
    }

    void InfoCommand::print_speed_type(SdFs& sd)
    {
        Serial.print("SdSpecVer: ");
        Serial.println(0.01 * scr.sdSpecVer());

        Serial.print("HighSpeedMode: ");
        if (scr.sdSpecVer() > 101 && sd.card()->cardCMD6(0X00FFFFFF, cmd6Data) && (2 & cmd6Data[13]))
        {
            Serial.println("true");
        }
        else
        {
            Serial.println("false");
        }
    }

    void InfoCommand::print_cid()
    {
        Serial.print("Manufacturer ID: 0x");
        Serial.println(cid.mid, HEX);

        Serial.print("OEM ID: ");
        Serial.print(cid.oid[0]);
        Serial.println(cid.oid[1]);

        Serial.print("Product: ");

        for (const char i : cid.pnm)
        {
            Serial.print(i);
        }
        Serial.println();

        Serial.print("Revision: ");
        Serial.print(cid.prvN());
        Serial.print('.');
        Serial.println(cid.prvM());

        Serial.print("Serial number: 0x");
        Serial.println(cid.psn(), HEX);

        Serial.print("Manufacturing date: ");
        Serial.print(cid.mdtMonth());
        Serial.print('/');
        Serial.println(cid.mdtYear());

        Serial.print("CRC: 0x");
        Serial.println(cid.crc, HEX);

        Serial.print("CID HEX: ");
        hexDump(&cid, sizeof(cid));
    }

    void InfoCommand::print_csd()
    {
        Serial.print("Card Size: ");
        Serial.print(0.000512 * csd.capacity());
        Serial.println(" MB");

        Serial.print("FlashEraseSize: ");
        Serial.print(csd.eraseSize());
        Serial.println(" blocks");

        Serial.print("EraseSingleBlock: ");
        if (csd.eraseSingleBlock())
        {
            Serial.println("true");
        }
        else
        {
            Serial.println("false");
        }

        Serial.print("DataAfterErase: ");
        if (scr.dataAfterErase())
        {
            Serial.println("ones");
        }
        else
        {
            Serial.println("zeros");
        }

        Serial.print("CSD HEX: ");
        hexDump(&csd, sizeof(csd));
    }

    void InfoCommand::print_ocr()
    {
        Serial.print("OCR: ");
        Serial.println(ocr, HEX);
    }

    bool InfoCommand::print_master_boot_record(SdFs& sd)
    {
        MbrSector_t mbr;
        bool valid = true;
        if (!sd.card()->readSector(0, reinterpret_cast<uint8_t*>(&mbr)))
        {
            return false;
        }

        Serial.println("SD Partition Table");
        Serial.println("part,boot,bgnCHS[3],type,endCHS[3],start,length");
        for (uint8_t ip = 1; ip < 5; ip++)
        {
            const MbrPart_t* pt = &mbr.part[ip - 1];
            if ((pt->boot != 0 && pt->boot != 0X80) ||
                getLe32(pt->relativeSectors) > csd.capacity())
            {
                valid = false;
            }


            Serial.print(static_cast<int>(ip), HEX);
            Serial.print(',');
            Serial.print(static_cast<int>(pt->boot), HEX);
            Serial.print(',');

            for (const unsigned char i : pt->beginCHS)
            {
                Serial.print(static_cast<int>(i));
                Serial.print(',');;
            }

            Serial.print(static_cast<int>(pt->type), HEX);
            Serial.print(',');

            for (const unsigned char i : pt->endCHS)
            {
                Serial.print(static_cast<int>(i), HEX);
                Serial.print(',');
            }
            Serial.print(getLe32(pt->relativeSectors));
            Serial.print(',');

            Serial.println(getLe32(pt->totalSectors));
        }

        if (!valid)
        {
            Serial.println("MBR not valid, assuming Super Floppy format.");
        }
        return true;
    }

    bool InfoCommand::print_volume(SdFs& sd)
    {
        if (!sd.volumeBegin())
        {
            return false;
        }
        Serial.println("Scanning FAT, please wait.");

        const int32_t freeClusterCount = sd.freeClusterCount();
        if (sd.fatType() <= 32)
        {
            Serial.print("Volume is FAT");
            Serial.println(sd.fatType());
        }
        else
        {
            Serial.println("Volume is exFAT");
        }

        Serial.print("SectorsPerCluster: ");
        Serial.println(sd.sectorsPerCluster());

        Serial.print("FatStartSector: ");
        Serial.println(sd.fatStartSector());

        Serial.print("DataStartSector: ");
        Serial.println(sd.dataStartSector());

        Serial.print("ClusterCount: ");
        Serial.println(sd.clusterCount());

        Serial.print("FreeClusterCount: ");
        if (freeClusterCount >= 0)
        {
            Serial.println(freeClusterCount);
        }
        else
        {
            return false;
        }
        return true;
    }
} // commands
