#include <Arduino.h>
#include <SD.h>

#include "commands/CommandParser.h"

constexpr int SD_CARD_CHIP_SELECT_PIN = 10;

void init_sd()
{
    Serial.println("Initializing SD card...");

    if (!SD.begin(SD_CARD_CHIP_SELECT_PIN))
    {
        Serial.println("initialization failed. Things to check:");
        Serial.println("1. is a card inserted?");
        Serial.println("2. is your wiring correct?");
        Serial.println("3. did you change the chipSelect pin to match your shield or module?");
        Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
        while (true);
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
    }

    init_sd();

    Serial.println("Ready");
}

void loop()
{
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.length() == 0)
    {
        return;
    }

    commands::ICommand* command = commands::CommandParser::Parse(cmd);
    command->execute();
}
