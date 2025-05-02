#include "Managers/DELPanelManager.h"
#include "const.h"
#include <LittleFS.h>
#include "Logs/DataLogger.h"

DELPanelManager::DELPanelManager(DS1307Clock *p_clock, DataLoggerManager *p_dataLoggerManager)
{
    this->m_panel = new WS2812Panel();
    this->m_clock = p_clock;
    this->m_dataloggerManager = p_dataLoggerManager;
    previousMillis = millis();

    currentAnimationIndex = 0;

    loadAnimationsFromFileSystem();

    Logger.log("Module DELPanelManager initialisé");
}

void DELPanelManager::setCountdownActive() 
{
    countdownActive = true;
}

const std::vector<Animation> & DELPanelManager::getAnimations()
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

const Animation* DELPanelManager::getAnimationByName(const String& name)
{
    const Animation* foundAnimation = nullptr;
    for (const Animation& animation: this->getAnimations())
    {
        if (animation.getName() == name)
        {
            foundAnimation = &animation;
            break;
        }
    }

    return foundAnimation;
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
        this->saveAnimations();
        return true;
    }
    return false;
}

void DELPanelManager::parseJsontoAnimation(const String &jsonString)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error)
    {
        Logger.error(String("Animation deserialization failed: ") + error.c_str());
        return;
    }

    JsonArray animationsArray = doc["animations"].as<JsonArray>();

    for (JsonObject animationJson : animationsArray)
    {
        Animation *animation = new Animation(); // Crée une nouvelle animation
        String name = animationJson["name"];
        animation->setName(name); // Défini le nom de l'animation

        JsonArray framesArray = animationJson["frames"];

        for (JsonObject frameJson : framesArray)
        {
            Frame frame(INTERVAL_200); // Ajuste la durée si besoin

            JsonArray pixelsArray = frameJson["pixels"];

            for (JsonObject pixelJson : pixelsArray)
            {
                uint8_t x = pixelJson["x"];
                uint8_t y = pixelJson["y"];
                JsonObject colorJson = pixelJson["color"];
                uint8_t r = colorJson["r"];
                uint8_t g = colorJson["g"];
                uint8_t b = colorJson["b"];

                Color *color = new Color(r, g, b);
                Pixel pixel(x, y, color);
                frame.addPixel(pixel);
            }

            animation->addFrame(frame);
        }

        addAnimationToVector(*animation);
    }
}

void DELPanelManager::loadAnimationsFromFileSystem()
{
    File file = LittleFS.open("/animations.json", "r");

    if (!file)
    {
        Logger.error("Erreur: Impossible d'ouvrir le fichier animations.json");
        return;
    }

    String jsonContent = "";
    while (file.available())
    {
        jsonContent += (char)file.read();
    }
    file.close();

    parseJsontoAnimation(jsonContent); 
}

bool DELPanelManager::loadAnimationFromJson(const String& jsonString)
{
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    
    if (error)
    {
        Logger.error(String("Animation deserialization failed: ") + error.c_str());
        return false;
    }

    Animation *animation = new Animation(); // Crée une nouvelle animation
    String name = doc["name"];
    animation->setName(name); // Défini le nom de l'animation

    JsonArray framesArray = doc["frames"];

    for (JsonObject frameJson : framesArray)
    {
        Frame frame(INTERVAL_200); // Ajuste la durée si besoin

        JsonArray pixelsArray = frameJson["pixels"];

        for (JsonObject pixelJson : pixelsArray)
        {
            uint8_t x = pixelJson["x"];
            uint8_t y = pixelJson["y"];
            JsonObject colorJson = pixelJson["color"];
            uint8_t r = colorJson["r"];
            uint8_t g = colorJson["g"];
            uint8_t b = colorJson["b"];

            Color *color = new Color(r, g, b);
            Pixel pixel(x, y, color);
            frame.addPixel(pixel);
        }

        animation->addFrame(frame);
    }

    for (int i = 0; i < this->animations.size(); i++)
    {
        if (animations[i].getName() == name)
        {
            this->deleteAnimationById(i);
            break;
        }
    }

    addAnimationToVector(*animation);
    saveAnimations();
    return true;
}

int DELPanelManager::getCurrentAnimationIndex()
{
    return this->currentAnimationIndex;
}

void DELPanelManager::addAnimationToVector(const Animation& animation)
{
    Logger.log("Animation ajouté: " + animation.getName());
    animations.push_back(animation);
}

void DELPanelManager::serializeAnimation(const Animation& animation, JsonObject& animObj)
{
    // Ajouter le nom de l'animation
    animObj["name"] = animation.getName();

    // Créer un tableau pour les frames
    JsonArray framesArray = animObj["frames"].to<JsonArray>();

    // Parcourir toutes les frames de cette animation
    std::vector<Frame> frames = animation.getFrames();
    for (Frame &frame : frames)
    {
        JsonObject frameObj = framesArray.add<JsonObject>();

        // Créer un tableau pour les pixels
        JsonArray pixelsArray = frameObj["pixels"].to<JsonArray>();

        // Parcourir tous les pixels de cette frame
        std::vector<Pixel> &pixels = frame.getPixels();

        for (Pixel &pixel : pixels)
        {
            JsonObject pixelObj = pixelsArray.add<JsonObject>();

            // Ajouter les coordonnées du pixel
            pixelObj["x"] = pixel.getX();
            pixelObj["y"] = pixel.getY();

            // Ajouter la couleur
            JsonObject colorObj = pixelObj["color"].to<JsonObject>();
            Color *color = pixel.getColor();
            colorObj["r"] = color->getR();
            colorObj["g"] = color->getG();
            colorObj["b"] = color->getB();
        }
    }
}

bool DELPanelManager::saveAnimations()
{
    if (!LittleFS.begin())
    {
        Logger.error("Erreur lors du montage de LittleFS");
        return false;
    }

    // Créer un document JSON
    JsonDocument doc;

    // Créer un tableau pour les animations
    JsonArray animationsArray = doc["animations"].to<JsonArray>();

    // Parcourir toutes les animations
    for (Animation &animation : animations)
    {
        JsonObject animObj = animationsArray.add<JsonObject>();
        serializeAnimation(animation, animObj);
    }

    // Ouvrir le fichier en mode écriture (cela va écraser le fichier existant)
    File file = LittleFS.open("/animations.json", "w");

    if (!file)
    {
        Logger.error("Erreur: Impossible d'ouvrir le fichier animations.json en écriture");
        return false;
    }

    // Sérialiser le JSON dans le fichier
    if (serializeJson(doc, file) == 0)
    {
        Logger.error("Erreur lors de l'écriture du JSON dans le fichier");
        file.close();
        return false;
    }

    file.close();
    return true;
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

void DELPanelManager::tick()
{
    unsigned long currentTime = millis();

    if (!animations.empty() && currentAnimationIndex < animations.size() && !this->countdownActive)
    {
        Animation &currentAnimation = animations[currentAnimationIndex];
        const std::vector<Frame>& frames = currentAnimation.getFrames();

        if (frames.empty())
        {
            return;
        }

        int frameIndex = currentAnimation.getCurrentFrameIndex();

        const Frame *currentFrame = currentAnimation.getFrame(frameIndex);
        if (currentFrame == nullptr)
        {
            return;
        }
        unsigned long frameDuration = currentFrame->getDuration();

        if (currentTime - lastFrameUpdateTime >= frameDuration)
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