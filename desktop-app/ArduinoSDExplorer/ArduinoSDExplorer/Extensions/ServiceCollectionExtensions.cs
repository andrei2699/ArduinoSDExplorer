using ArduinoSDExplorer.Services;
using ArduinoSDExplorer.ViewModels;
using Microsoft.Extensions.DependencyInjection;

namespace ArduinoSDExplorer.Extensions;

public static class ServiceCollectionExtensions
{
    public static void AddCommonServices(this IServiceCollection services)
    {
        services.AddTransient<IComPortsLoaderService, ComPortsLoaderService>()
            .AddTransient<ISdCardOperationsService, SdCardOperationsService>()
            .AddSingleton<ILoggerService, LoggerService>()
            .AddTransient<MainWindowViewModel>();
    }
}
