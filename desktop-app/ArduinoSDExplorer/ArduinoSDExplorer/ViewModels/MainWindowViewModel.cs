using System.Collections.ObjectModel;
using ArduinoSDExplorer.Models;
using ArduinoSDExplorer.Services;
using ReactiveUI;

namespace ArduinoSDExplorer.ViewModels;

public partial class MainWindowViewModel(IComPortsLoaderService comPortsLoaderService) : ViewModelBase
{
    public ObservableCollection<string> ComPorts { get; set; } = [];

    public string? SelectedComPort
    {
        get => _selectedComPort;
        set => this.RaiseAndSetIfChanged(ref _selectedComPort, value);
    }

    public long BaudRate { get; set; } = 9600;

    public string SearchText { get; set; } = "";

    public ObservableCollection<Node> Nodes { get; } =
    [
        new("Animals", [
            new Node("Mammals", [new Node("Lion"), new Node("Cat"), new Node("Zebra")])
        ])
    ];

    public string Logs { get; set; } = "";


    private string? _selectedComPort;

    public void LoadComPorts()
    {
  var comPorts = comPortsLoaderService.GetComPorts();

        ComPorts.Clear();
        foreach (var port in comPorts)
        {
            ComPorts.Add(port);
        }

        SelectedComPort = comPorts.Count > 0 ? comPorts[0] : null;
    }

    public void ReadSdCard()
    {
        // TODO FIXIT: Implement the logic to read the SD card here
    }
}
