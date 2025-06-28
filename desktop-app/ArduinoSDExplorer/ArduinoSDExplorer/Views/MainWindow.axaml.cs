using ArduinoSDExplorer.ViewModels;
using Avalonia.Controls;
using Avalonia.Interactivity;

namespace ArduinoSDExplorer.Views;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
    }

    private void Control_OnLoaded(object? sender, RoutedEventArgs e)
    {
        if (DataContext is MainWindowViewModel viewModel)
        {
            viewModel.LoadComPortsCommand();
        }
    }
}
