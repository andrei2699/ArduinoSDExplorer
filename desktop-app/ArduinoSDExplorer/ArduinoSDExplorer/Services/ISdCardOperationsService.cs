using ArduinoSDExplorer.Models;

namespace ArduinoSDExplorer.Services;

public interface ISdCardOperationsService
{
    void Connect(SdCard sdCard);

    void Disconnect(SdCard sdCard);
}
