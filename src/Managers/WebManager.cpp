#include "Managers/WebManager.h"
#include "WebServer.h"
#include "LittleFS.h"
#include <uri/UriBraces.h>
#include "Logs/DataLogger.h"

WebManager::WebManager(ConfigManager *p_configManager, DataLoggerManager *p_dataLoggerManager, DELPanelManager *p_delPanelManager, LaunchManager *p_launchManager)
{
    m_webServer = new WebServer(80);
    this->m_configManager = p_configManager;
    this->m_dataLoggerManager = p_dataLoggerManager;
    this->m_delPanelManager = p_delPanelManager;
    this->m_launchManager = p_launchManager;

    m_webServer->on("/", [this]()
                    { this->handleRoot(); });

    m_webServer->on("/index.html", [this]()
                    {
        if (!m_configManager->isConfigReceived())
        {
            this->handleRoot();
            return;
        }
        File index = LittleFS.open("/index.html", "r");

        if (!index)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(index, "text/html");
        index.close(); });

    m_webServer->on("/lancement.html", [this]()
                    {
        if (!m_configManager->isConfigReceived())
        {
            this->handleRoot();
            return;
        }
        File lancement = LittleFS.open("/lancement.html", "r");

        if (!lancement)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(lancement, "text/html");
        lancement.close(); });

    m_webServer->on("/animations.html", [this]()
                    {
        if (!m_configManager->isConfigReceived())
        {
            this->handleRoot();
            return;
        }
        File animations = LittleFS.open("/animations.html", "r");

        if (!animations)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(animations, "text/html");
        animations.close(); });

    m_webServer->on("/logs.html", [this]()
                    {
        if (!m_configManager->isConfigReceived())
        {
            this->handleRoot();
            return;
        }
        File logs = LittleFS.open("/logs.html", "r");

        if (!logs)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(logs, "text/html");
        logs.close(); });

    m_webServer->on("/api/config", HTTP_POST, [this]()
                    { this->sendConfigToManager(); });

    m_webServer->on("/api/launch", HTTP_POST, [this]()
                    { this->sendLaunchToManager(); });

    m_webServer->on("/api/animation", HTTP_GET, [this]()
                    { this->getAnimations(); });

    m_webServer->on("/api/animation/active", HTTP_GET, [this]()
                    { this->getActiveAnimationIndex(); });

    m_webServer->on(UriBraces("/api/animation/{}"), HTTP_DELETE, [this]()
                    { this->deleteAnimation(atoi(this->m_webServer->pathArg(0).c_str())); });

    m_webServer->on(UriBraces("/api/animation/{}"), HTTP_POST, [this]()
                    { this->selectAnimation(atoi(this->m_webServer->pathArg(0).c_str())); });

    m_webServer->on("/api/logs", HTTP_GET, [this]()
                    { this->getLogs(); });

    m_webServer->on("/favicon.ico", HTTP_GET, [this]()
                    {
                        this->m_webServer->send(204); // No Content
                    });

    m_webServer->serveStatic("/bootstrap/js/bootstrap.min.js", LittleFS, "/bootstrap/js/bootstrap.min.js");
    m_webServer->serveStatic("/bootstrap/css/bootstrap.min.css", LittleFS, "/bootstrap/css/bootstrap.min.css");
    m_webServer->serveStatic("/bootstrap/js/bootstrap.min.js.map", LittleFS, "/bootstrap/js/bootstrap.min.js.map");
    m_webServer->serveStatic("/bootstrap/css/bootstrap.min.css.map", LittleFS, "/bootstrap/css/bootstrap.min.css.map");

    m_webServer->onNotFound([this]()
                            { Serial.println(this->m_webServer->uri()); });

    m_webServer->begin();

    Logger.log("Module WebManager initialisé");
}

void WebManager::getActiveAnimationIndex()
{
    this->m_webServer->send(200, "text/plain", String(this->m_delPanelManager->getCurrentAnimationIndex()));
}

void WebManager::getLogs()
{
    JsonDocument doc;
    JsonArray logs = doc.to<JsonArray>();

    for (const LogEntry &entry : Logger.getLogs())
    {
        JsonObject logEntry = logs.add<JsonObject>();
        logEntry["message"] = entry.message;

        switch (entry.type)
        {
        case LogType::Message:
            logEntry["type"] = "message";
            break;
        case LogType::Error:
            logEntry["type"] = "error";
            break;
        default:
            logEntry["type"] = "message";
            break;
        }
    }

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    m_webServer->send(200, "application/json", jsonResponse);
}

void WebManager::getAnimations()
{
    JsonDocument doc;
    JsonArray animationArray = doc.to<JsonArray>();

    std::vector<Animation> animations = m_delPanelManager->getAnimations();
    for (int i = 0; i < animations.size(); i++)
    {
        JsonObject animationObj = animationArray.add<JsonObject>();
        animationObj["id"] = i;
        animationObj["name"] = animations[i].getName();
    }

    String jsonResponse;
    serializeJson(doc, jsonResponse);

    m_webServer->send(200, "application/json", jsonResponse);
}

void WebManager::getIsConfigReceived()
{
    String response = m_configManager->isConfigReceived() ? "true" : "false";
    m_webServer->send(200, "application/json", response);
}

void WebManager::deleteAnimation(uint8_t id)
{
    if (m_delPanelManager->deleteAnimationById(id))
    {
        m_webServer->send(204);
    }
    else
    {
        m_webServer->send(400, "application/json", "Cannot delete animation");
    }
}

void WebManager::selectAnimation(uint8_t id)
{
    if (m_delPanelManager->setCurrentAnimationIndex(id))
    {
        m_webServer->send(200, "application/json", "Animation selected succesfully");
    }
    else
    {
        m_webServer->send(400, "application/json", "Cannot select animation");
    }
}

void WebManager::handleRoot()
{
    if (!m_configManager->isConfigReceived())
    {
        File capteurs = LittleFS.open("/capteurs.html", "r");

        if (!capteurs)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(capteurs, "text/html");
        capteurs.close();
    }
    else
    {
        File index = LittleFS.open("/index.html", "r");

        if (!index)
        {
            m_webServer->send(500, "text/plain", "Failed to open index.html");
            Logger.error("Failed to open index.html");
            return;
        }

        m_webServer->streamFile(index, "text/html");
        index.close();
    }
}

void WebManager::sendConfigToManager()
{
    String jsonRequest = this->m_webServer->arg("plain");

    JsonDocument doc;

    std::vector<String> sensorsToInit = {};
    std::vector<String> dataTypesChosen = {};

    DeserializationError error = deserializeJson(doc, jsonRequest);

    if (!error)
    {

        JsonArray sensorsName = doc["capteurs"].as<JsonArray>();
        for (JsonVariant sensor : sensorsName)
        {
            sensorsToInit.push_back(sensor.as<String>());
        }

        JsonArray datasName = doc["donnees"].as<JsonArray>();
        for (JsonVariant dataName : datasName)
        {
            dataTypesChosen.push_back(dataName.as<String>());
        }

        this->m_configManager->setDateAndTimeToInit(doc["dateEtHeure"]);
        this->m_configManager->setSensorsToInit(sensorsToInit);
        this->m_configManager->setDataTypesChosen(dataTypesChosen);
        this->m_configManager->setClockTime();

        JsonDocument responseDoc;
        responseDoc["Status"] = "success";
        responseDoc["message"] = "Configuration traitée";
        String responseJson;
        serializeJson(responseDoc, responseJson);

        this->m_webServer->send(200, "application/json", responseJson);
    }
    else
    {
        Logger.error("Erreur de désérialisation JSON : " + String(error.c_str()));
        this->m_webServer->send(400, "application/json", R"({"status":"error","message":"JSON invalide"})");
    }

    this->m_configManager->notifyConfigReceived();
}

void WebManager::sendLaunchToManager()
{
    if (this->m_launchManager->getCountDownActive())
    {
        String response = "{\"error\": \"Décompte déjà lancé\"}";
        this->m_webServer->send(400, "application/json", response);
        return;
    }

    this->m_launchManager->activateCountdown();

    this->m_webServer->send(200);
}

void WebManager::loop()
{
    m_webServer->handleClient();
}