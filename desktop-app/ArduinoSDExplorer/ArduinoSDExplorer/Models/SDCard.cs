using System.IO.Ports;

namespace ArduinoSDExplorer.Models;

public record SdCard(string ComPort, int BaudRate)
{
    private readonly SerialPort _serial = new(ComPort, BaudRate);
    private SerialDataReceivedEventHandler? _serialOnDataReceived;

    public void Connect(OnDataReceivedEventHandler onDataReceived)
    {
        if (_serial.IsOpen)
        {
            _serial.Close();
        }


        _serialOnDataReceived = (_, _) => onDataReceived(_serial.ReadExisting());
        _serial.DataReceived += _serialOnDataReceived;

        _serial.Open();
    }

    public void Disconnect()
    {
        if (!_serial.IsOpen)
        {
            return;
        }

        _serial.DataReceived -= _serialOnDataReceived;
        _serial.Close();
    }
}

public delegate void OnDataReceivedEventHandler(string data);
