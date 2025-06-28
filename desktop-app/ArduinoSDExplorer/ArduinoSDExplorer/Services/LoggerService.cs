using System;

namespace ArduinoSDExplorer.Services;

public class LoggerService : ILoggerService
{
    private Action<string>? _loggingAction;

    public void Attach(Action<string> loggingAction)
    {
        _loggingAction = loggingAction;
    }

    public void LogArduino(string message)
    {
        var logMessage = "[Arduino] " + message + Environment.NewLine;
        Console.Write(logMessage);
        _loggingAction?.Invoke(logMessage);
    }

    public void LogSystem(string message)
    {
        var logMessage = "[System] " + message + Environment.NewLine;
        Console.Write(logMessage);
        _loggingAction?.Invoke(logMessage);
    }
}
