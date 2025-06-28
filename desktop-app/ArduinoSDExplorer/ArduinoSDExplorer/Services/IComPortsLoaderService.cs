using System.Collections.Generic;

namespace ArduinoSDExplorer.Services;

public interface IComPortsLoaderService
{
    List<string> GetComPorts();
}
