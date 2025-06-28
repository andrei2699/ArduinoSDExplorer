using System;

namespace ArduinoSDExplorer.Services;

public interface ILoggerService
{
    void Attach(Action<string> loggingAction);

    void LogArduino(string message);

    void LogSystem(string message);
}
