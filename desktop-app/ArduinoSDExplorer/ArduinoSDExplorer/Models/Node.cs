using System.Collections.ObjectModel;

namespace ArduinoSDExplorer.Models;

public class Node
{
    public ObservableCollection<Node>? SubNodes { get; }
    public string Title { get; }

    public Node(string title)
    {
        Title = title;
    }

    public Node(string title, ObservableCollection<Node> subNodes)
    {
        Title = title;
        SubNodes = subNodes;
    }
}
