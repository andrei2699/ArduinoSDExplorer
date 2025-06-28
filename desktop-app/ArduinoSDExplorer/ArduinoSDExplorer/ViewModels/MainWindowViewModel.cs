using System.Collections.ObjectModel;
using ArduinoSDExplorer.Models;
using ArduinoSDExplorer.Services;
using ReactiveUI.Fody.Helpers;

namespace ArduinoSDExplorer.ViewModels;

public partial class MainWindowViewModel(
    IComPortsLoaderService comPortsLoaderService,
    ISdCardOperationsService sdCardOperationsService,
    ILoggerService loggerService) : ViewModelBase
{
    public ObservableCollection<string> ComPorts { get; set; } = [];

    [Reactive] public string? SelectedComPort { get; set; }
    [Reactive] public int BaudRate { get; set; } = 9600;

    [Reactive] public string SearchText { get; set; } = "";

    public ObservableCollection<Node> Nodes { get; } =
    [
        new("Animals", [
            new Node("Mammals", [new Node("Lion"), new Node("Cat"), new Node("Zebra")])
        ])
    ];

    [Reactive] public string Logs { get; set; } = "";

    private SdCard? _sdCard;


    public void LoadComPortsCommand()
    {
        var comPorts = comPortsLoaderService.GetComPorts();

        ComPorts.Clear();
        foreach (var port in comPorts)
        {
            ComPorts.Add(port);
        }

        SelectedComPort = comPorts.Count > 0 ? comPorts[0] : null;
    }

    public void ConnectToSdCardCommand()
    {
        if (SelectedComPort is null)
        {
            return;
        }

        loggerService.Attach(message => Logs += message);

        if (_sdCard is not null)
        {
            sdCardOperationsService.Disconnect(_sdCard);
        }

        _sdCard = new SdCard(SelectedComPort, BaudRate);
        sdCardOperationsService.Connect(_sdCard);
    }

    public void ReadSdCardCommand()
    {
        // TODO FIXIT: Implement the logic to read the SD card here
    }

    public void ClearLogsCommand()
    {
        Logs = "";
    }
}
