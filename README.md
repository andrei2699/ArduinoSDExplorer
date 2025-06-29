# ArduinoSDExplorer

A Windows desktop application for exploring and managing files on an Arduino SD card via serial communication.

## Features

- List available COM ports
- Connect to Arduino devices
- Browse SD card contents
- Upload, download, and delete files on the SD card

## Pinout

### Arduino Uno

| Pin | Function     |
|-----|--------------|
| 10  | SD Card CS   |
| 11  | SD Card MOSI |
| 12  | SD Card MISO |
| 13  | SD Card SCK  |

### Arduino Mega

| Pin | Function     |
|-----|--------------|
| 53  | SD Card CS   |
| 51  | SD Card MOSI |
| 50  | SD Card MISO |
| 52  | SD Card SCK  |

## Resources

- [protocol.md](docs/protocol.md) for details about the serial communication protocol used between the application and
  Arduino.

- [schematics](docs/schematics) for the schematic of the Arduino setup.

![schematic](docs/schematics/schematic_mega.svg)
