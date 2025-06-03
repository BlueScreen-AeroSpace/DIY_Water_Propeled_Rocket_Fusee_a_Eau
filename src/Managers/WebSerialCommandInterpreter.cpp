#include "Managers/WebSerialCommandInterpreter.h"
#include "Logs/DataLogger.h"
#include "Animation/AnimationSerializer.h"

WebSerialCommandInterpreter::WebSerialCommandInterpreter(DELPanelManager *p_delPanelManager)
{
    this->m_delPanelManager = p_delPanelManager;
    Logger.log("Module WebSerialCommandInterpreter initialisé");
}

bool WebSerialCommandInterpreter::interpret(const uint8_t *commandBytes)
{
    bool error = false;
    uint16_t offset = 0;
    uint8_t commandStringLength = commandBytes[offset++];
    if (commandStringLength > 64)
    {
        Logger.error("Command length is too long.");
        return false;
    }
    char commandBuffer[commandStringLength + 1]; //+1 pour le null termination byte

    for (int i = 0; i < commandStringLength; i++)
    {
        commandBuffer[i] = commandBytes[offset++];
    }
    commandBuffer[commandStringLength] = '\0';
    String command = String(commandBuffer);

    if (command == "addAnimation")
    {
        Animation animation = AnimationSerializer::deserialize(commandBytes, offset);
        for (const Animation &existingAnim : m_delPanelManager->getAnimations())
        {
            if (animation.getName() == existingAnim.getName())
            {
                m_delPanelManager->deleteAnimationByName(existingAnim.getName());
                break;
            }
        }
        m_delPanelManager->addAnimationToVector(animation);
        m_delPanelManager->saveAnimation(animation);
        delete[] commandBytes;
        return true;
    }
    else if (command == "getAnimation")
    {
        uint8_t argLength = commandBytes[offset++];
        if (argLength > 255)
        {
            Logger.error("Arg length too long");
            return false;
        }

        char titleBuffer[argLength + 1]; // +1 pour le null termination byte
        memcpy(titleBuffer, &commandBytes[offset], argLength);
        titleBuffer[argLength] = '\0';
        String title = String(titleBuffer);

        Logger.log("Received animation: " + title);

        const Animation *animation = m_delPanelManager->getAnimationByName(title);
        if (animation == nullptr)
        {
            Logger.error("No animation with this name" + title);
            return false;
        }
        size_t length = 0;
        const uint8_t *data = AnimationSerializer::serialize(*animation, length);

        std::vector<uint8_t> escapedData = escapeData(data, length);

        size_t totalLength = 1 + escapedData.size() + 1;
        uint8_t *finalMessage = new uint8_t[totalLength];

        size_t pos = 0;
        finalMessage[pos++] = START_MARKER;
        memcpy(finalMessage + pos, escapedData.data(), escapedData.size());
        pos += escapedData.size();
        finalMessage[pos++] = END_MARKER;

        for (size_t i = 0; i < totalLength; i += CHUNK_SIZE)
        {
            size_t chunkSize = min(CHUNK_SIZE, totalLength - i);
            Serial.write(finalMessage + i, chunkSize);
            Serial.flush();
            delay(10);
        }

        delete[] data;
        delete[] finalMessage;
        delete[] commandBytes;
        return true;
    }
    else if (command == "getAnimationsNames")
    {
        size_t length = 2; // Two bytes for total length
        const std::vector<Animation> &animations = m_delPanelManager->getAnimations();
        length += animations.size(); // 1 byte for each length

        for (const Animation &animation : animations)
        {
            length += animation.getName().length();
        }

        uint8_t *data = new uint8_t[length];
        size_t animOffset = 0;
        for (const Animation &animation : animations)
        {
            const String &name = animation.getName();
            size_t len = name.length();
            data[animOffset++] = static_cast<uint8_t>(len);
            memcpy(data + animOffset, name.c_str(), len);
            animOffset += len;
        }

        size_t totalLength = 1 + 2 + length + 1;
        uint8_t *finalMessage = new uint8_t[totalLength];

        size_t pos = 0;
        finalMessage[pos++] = START_MARKER;
        finalMessage[pos++] = (length >> 8) & 0xFF;
        finalMessage[pos++] = length & 0xFF;
        memcpy(finalMessage + pos, data, length);
        pos += length;
        finalMessage[pos++] = END_MARKER;

        for (size_t i = 0; i < totalLength; i += CHUNK_SIZE)
        {
            size_t chunkSize = min(CHUNK_SIZE, totalLength - i);
            Serial.write(finalMessage + i, chunkSize);
            delay(10);
        }

        delete[] data;
        delete[] finalMessage;
        delete[] commandBytes;
        return true;
    }
    Logger.log("Command received: " + command);

    return false;
}

std::vector<uint8_t> WebSerialCommandInterpreter::escapeData(const uint8_t *data, size_t length)
{
    std::vector<uint8_t> escaped;

    for (size_t i = 0; i < length; i++)
    {
        uint8_t byte = data[i];
        if (byte == START_MARKER || byte == END_MARKER || byte == ESCAPE_BYTE)
        {
            escaped.push_back(ESCAPE_BYTE);
            escaped.push_back(byte ^ 0x20);
        }
        else
        {
            escaped.push_back(byte);
        }
    }

    return escaped;
}