#include "Managers/DELPanelManager.h"
#include "const.h"
#include <LittleFS.h>
#include "Logs/DataLogger.h"
#include "Animation/AnimationSerializer.h"

DELPanelManager::DELPanelManager(DS1307Clock *p_clock, DataLoggerManager *p_dataLoggerManager)
{
    this->m_panel = new WS2812Panel();
    this->m_clock = p_clock;
    this->m_dataloggerManager = p_dataLoggerManager;
    previousMillis = millis();

    currentAnimationIndex = 0;
    this->loadAnimations();

    Logger.log("Module DELPanelManager initialisé");
}

void DELPanelManager::setCountdownActive()
{
    countdownActive = true;
}

const std::vector<Animation> &DELPanelManager::getAnimations()
{
    return this->animations;
}

bool DELPanelManager::getCountDownActive()
{
    return this->countdownActive;
}

bool DELPanelManager::setCurrentAnimationIndex(u_int8_t p_index)
{
    if (p_index < animations.size() && p_index >= 0)
    {
        currentAnimationIndex = p_index;
        m_panel->eraseScreen();
        return true;
    }
    return false;
}
Animation *DELPanelManager::getAnimationById(int p_index)
{
    if (p_index < animations.size() && p_index >= 0)
    {
        return &animations[p_index];
    }
    return nullptr;
}

const Animation *DELPanelManager::getAnimationByName(const String &name)
{
    const Animation *foundAnimation = nullptr;
    for (const Animation &animation : this->getAnimations())
    {
        if (animation.getName() == name)
        {
            foundAnimation = &animation;
            break;
        }
    }

    return foundAnimation;
}

bool DELPanelManager::deleteAnimationByName(const String& name)
{
    for (int i = 0; i < this->animations.size(); i++)
    {
        if (animations[i].getName() == name)
        {
            this->animations.erase(animations.begin() + i);
            return true;
        }
    }
    return false;
}

bool DELPanelManager::deleteAnimationById(int p_index)
{
    if (p_index < animations.size() && p_index >= 0)
    {
        animations.erase(animations.begin() + p_index);
        if (p_index > 0)
        {
            currentAnimationIndex--;
        }
        return true;
    }
    return false;
}

int DELPanelManager::getCurrentAnimationIndex()
{
    return this->currentAnimationIndex;
}

void DELPanelManager::showTime() // Affiche l'heure sur le panneau
{
    String time = this->m_clock->getActualTimeNoSec();
    this->m_panel->showTime(time);
}

void DELPanelManager::theFinalCountdown() // Compte à rebours
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= INTERVAL_1)
    {
        previousMillis = currentMillis;

        this->m_panel->showCountdown(countdownValue); // Affiche le nombre sur le panneau

        if (countdownValue == 0)
        {
            this->m_dataloggerManager->setIsReadyToLogData();
            countdownActive = false;
            countdownValue = 10;
        }
        else
        {
            countdownValue--;
        }
    }
}

void DELPanelManager::loadAnimations()
{
    File dir = LittleFS.open("/animations");

    if (!dir || !dir.isDirectory())
    {
        Logger.error("Failed to open /animations directory");
    }

    File file = dir.openNextFile();
    while (file)
    {
        String fileName = file.name();

        if (!file.isDirectory() && fileName.endsWith(".bin"))
        {
            size_t size = file.size();
            uint8_t *buffer = new uint8_t[size];

            file.read(buffer, size);
            Animation animation = AnimationSerializer::deserialize(buffer, 0);

            this->addAnimationToVector(animation);

            delete[] buffer;
            Logger.log("Loaded animation: " + animation.getName());
        }
        file = dir.openNextFile();
    }
}

void DELPanelManager::addAnimationToVector(const Animation &animation)
{
    this->animations.push_back(animation);
}

bool DELPanelManager::saveAnimation(const Animation &animation)
{
    if (!LittleFS.exists("/animations"))
    {
        if (!LittleFS.mkdir("/animations"))
        {
            Logger.error("Failed to create the animations folder");
            return false;
        }
    }

    String path = String("/animations/") + animation.getNameNormalized() + String(".bin");
    File file = LittleFS.open(path, "w");

    if (!file)
    {
        Logger.error("Failed to create file " + path);
        return false;
    }
    size_t animationSize = 0;
    const uint8_t *animationBytes = AnimationSerializer::serialize(animation, animationSize);

    file.write(animationBytes, animationSize);
    return true;
}

void DELPanelManager::tick()
{
    unsigned long currentTime = millis();
    static bool frameNull = false;
    if (!animations.empty() && currentAnimationIndex < animations.size() && !this->countdownActive)
    {
        Animation &currentAnimation = animations[currentAnimationIndex];
        const std::vector<Frame> &frames = currentAnimation.getFrames();

        if (frames.empty())
        {
            return;
        }

        int frameIndex = currentAnimation.getCurrentFrameIndex();

        const Frame *currentFrame = currentAnimation.getFrame(frameIndex);
        if (currentFrame == nullptr)
        {
            frameNull = true;
            if (frameNull) 
            {
                Logger.error("Null frame");
            }
            return;
        }

        if (currentTime - lastFrameUpdateTime >= INTERVAL_200)
        {
            lastFrameUpdateTime = currentTime;

            if (frameIndex == 0)
            {
                this->m_panel->eraseScreen(); // Efface l'ecran
            }

            this->m_panel->drawFrame(*currentFrame); // Affiche la frame
            currentAnimation.setCurrentFrameIndex((frameIndex + 1) % frames.size());
        }
        m_panel->show(); // Met a jour l'affichage
    }
    else if (this->countdownActive)
    {
        this->theFinalCountdown();
    }
    else
    {
        this->m_panel->eraseScreen();
        m_panel->show();
    }
}