#include <ArduinoJson.h>
#include "WebServer.h"
#include "ConfigManager.h"
#include "LaunchManager.h"
#include "DELPanelManager.h"
#include "Managers/DataLoggerManager.h"
#include <vector>

class WebManager
{
public:
    WebManager(ConfigManager *p_configManager, DataLoggerManager* p_dataLoggerManager, DELPanelManager* p_delPanelManager, LaunchManager* m_launchManager);
    void loop();
private:
    WebServer *m_webServer;
    ConfigManager *m_configManager;
    LaunchManager* m_launchManager;
    DataLoggerManager* m_dataLoggerManager;
    DELPanelManager* m_delPanelManager;
    void handleRoot();
    void sendConfigToManager();
    void sendLaunchToManager();
    void getAnimations();
    void deleteAnimation(uint8_t id);
    void selectAnimation(uint8_t id);
    void getIsConfigReceived();
    void getLogs();
    void getActiveAnimationIndex();
    const String page = "<html><body>Test</body></html>";
};
