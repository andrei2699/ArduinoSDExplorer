using System;
using ArduinoSDExplorer.Models;

namespace ArduinoSDExplorer.Services;

public class SdCardOperationsService(ILoggerService loggerService) : ISdCardOperationsService
{
    public void Connect(SdCard sdCard)
    {
        loggerService.LogSystem($"Connecting to SD card... on port: {sdCard.ComPort} at baud rate: {sdCard.BaudRate}");
        try
        {
            sdCard.Connect(data => loggerService.LogArduino($"Received data: {data}"));
            loggerService.LogSystem("Connected successfully.");
        }
        catch (Exception ex)
        {
            loggerService.LogSystem($"Failed to connect: {ex.Message}");
        }
    }

    public void Disconnect(SdCard sdCard)
    {
        loggerService.LogSystem($"Disconnecting from SD card on port: {sdCard.ComPort}");
        try
        {
            sdCard.Disconnect();
            loggerService.LogSystem("Disconnected successfully.");
        }
        catch (Exception ex)
        {
            loggerService.LogSystem($"Failed to disconnect: {ex.Message}");
        }
    }
}
