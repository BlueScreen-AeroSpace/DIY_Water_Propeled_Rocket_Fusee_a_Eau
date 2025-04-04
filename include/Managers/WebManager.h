#include <ArduinoJson.h>
#include "WebServer.h"
#include "SensorManager.h"
class WebManager
{
public:
    WebManager(SensorManager* p_sensorManager);
    void loop();

private:
    WebServer* m_webserver;
    SensorManager* m_sensorManager;
    void handleRoot();

    const String page = "<html><body>Test</body></html>";
};
