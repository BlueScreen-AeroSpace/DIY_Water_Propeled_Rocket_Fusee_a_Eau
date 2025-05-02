#include "Managers/WebSerialCommandInterpreter.h"
#include "Logs/DataLogger.h"

WebSerialCommandInterpreter::WebSerialCommandInterpreter(DELPanelManager *p_delPanelManager)
{
    this->m_delPanelManager = p_delPanelManager;
    Logger.log("Module WebSerialCommandInterpreter initialisé");
}

bool WebSerialCommandInterpreter::interpret(const String& command, const JsonArray& arguments)
{
    std::vector<String> params;
    const size_t numArgs = arguments.size();
    for (size_t i = 0; i < numArgs; i++)
    {
        params.push_back(arguments[i].as<String>());
    }

    bool error = false;

    if (command == "addAnimation")
    {
        if (params.size() != 1)
        {
            return true;
        }

        this->m_delPanelManager->loadAnimationFromJson(params[0]);
    } 
    else if (command == "getAnimation")
    {
        if (params.size() != 1)
        {
            return true;
        }

        std::vector<Animation> animations = m_delPanelManager->getAnimations();
        Animation* foundAnimation = nullptr;
        for (Animation& animation: animations)
        {
            if (animation.getName() == params[0])
            {
                foundAnimation = &animation;
                break;
            }
        }

        if (foundAnimation == nullptr)
        {
            return true;
        }

        JsonDocument doc;
        JsonObject animObj = doc.to<JsonObject>();
        m_delPanelManager->serializeAnimation(*foundAnimation, animObj);

        String jsonString;
        serializeJson(animObj, jsonString);

        sendMessage(jsonString);
    }
    else if (command == "deleteAnimation")
    {
        if (params.size() != 1)
        {
            return true;
        }

        std::vector<Animation> animations = m_delPanelManager->getAnimations();
        int animationIndex = -1;
        for (int i = 0; i < animations.size(); i++)
        {
            if (animations[i].getName() == params[0])
            {
                animationIndex = i;
                break;
            }
        }

        if (animationIndex == -1)
        {
            return true;
        }

        this->m_delPanelManager->deleteAnimationById(animationIndex);
    }
    else if (command == "getAnimationsNames")
    {
        if (params.size() != 0)
        {
            return true;
        }

        JsonDocument doc;
        JsonArray jsonArray = doc.to<JsonArray>();

        for (Animation animation: this->m_delPanelManager->getAnimations())
        {
            jsonArray.add(animation.getName());
        }

        String jsonString;
        serializeJson(jsonArray, jsonString);
        
        sendMessage(jsonString);
    }

    return false;
}

void WebSerialCommandInterpreter::sendMessage(const String& message)
{
    Serial.println("<<START>>");
    Serial.println(message);
    Serial.println("<<END>>");   
}