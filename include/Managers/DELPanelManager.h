#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include "const.h"
#include "Modules/WS2812Panel.h"
#include "Modules/DS1307Clock.h"

#include <vector>
#include <ArduinoJson.h>
#include "Animation/Animation.h"
#include "Animation/Frame.h"
#include "Animation/Pixel.h"
#include <LittleFS.h>

#include "Managers/DataLoggerManager.h"

class DELPanelManager
{
private:
    WS2812Panel *m_panel;
    DS1307Clock *m_clock;
    int countdownValue = 10;
    unsigned long previousMillis;
    bool countdownActive = false;
    DataLoggerManager *m_dataloggerManager;

    unsigned long lastUpdateTime = 0;

    std::vector<Animation> animations; // Vector to hold animation functions
    int currentAnimationIndex = 0;         // Index of the current animation

    unsigned long lastFrameUpdateTime = 0; // Temps du dernier changement de frame

public:
    DELPanelManager(DS1307Clock *p_clock, DataLoggerManager *p_dataLoggerManager);
    Animation *getAnimationById(int p_index);
    const Animation *getAnimationByName(const String& name);
    bool deleteAnimationById(int p_index);
    const std::vector<Animation> &getAnimations();
    bool setCurrentAnimationIndex(u_int8_t p_index);
    void showTime();
    void theFinalCountdown();
    void setCountdownActive();
    void parseJsontoAnimation(const String &jsonString);
    void loadAnimationsFromFileSystem();
    void addAnimationToVector(const Animation& animation);
    bool loadAnimationFromJson(const String &jsonString);
    bool saveAnimations();
    bool getCountDownActive();
    int getCurrentAnimationIndex();
    void tick();
    void serializeAnimation(const Animation& animation, JsonObject& animObj);
};