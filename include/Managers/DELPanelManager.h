#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include "const.h"
#include "Modules/WS2812Panel.h"
#include "Modules/DS1307Clock.h"

class DELPanelManager
{
private:
    WS2812Panel *panel;
    DS1307Clock *clock;
    int countdownValue = 10;
    unsigned long previousMillis;
    bool countdownActive = false;

    unsigned long lastUpdateTime = 0;
    int currentFunctionIndex = 0;

public:
    DELPanelManager(WS2812Panel *_panel, DS1307Clock *_clock);
    void showTime();
    void theFinalCountdown();
    void showAnimationOne();
    void setCountdownActive();
    void tick();
};