#include <Arduino.h>
#include "SdFat.h"
#include "commands/CommandParser.h"

constexpr uint8_t SD_CS_PIN = SS;

auto sdConfig = SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16));
SdFs sd;

constexpr int SD_CARD_CHIP_SELECT_PIN = 10;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        yield();
    }

    Serial.println("Ready");
}

void loop()
{
    while (!Serial.available())
    {
        yield();
    }

    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.length() == 0)
    {
        return;
    }

    commands::ICommand* command = commands::CommandParser::Parse(cmd);
    command->execute(sdConfig, sd);
}
