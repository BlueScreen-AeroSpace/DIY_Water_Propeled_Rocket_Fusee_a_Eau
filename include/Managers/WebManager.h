#include <ArduinoJson.h>
#include "WebServer.h"
#include "ConfigManager.h"
#include <vector>

class WebManager
{
public:
    WebManager(ConfigManager *p_configManager);
    void loop();

private:
    WebServer *m_webserver;
    ConfigManager *m_configManager;
    void handleRoot();
    void sendConfigToManager();
    const String page = "<html><body>Test</body></html>";
};
