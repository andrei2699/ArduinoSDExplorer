using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;

namespace ArduinoSDExplorer.Services;

public class ComPortsLoaderService : IComPortsLoaderService
{
    public List<string> GetComPorts()
    {
        string[] ports = SerialPort.GetPortNames();

        return ports.ToList();
    }
}
