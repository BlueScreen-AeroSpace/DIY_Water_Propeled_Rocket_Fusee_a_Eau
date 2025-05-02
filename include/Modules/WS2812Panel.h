#pragma once
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include "Animation/Frame.h"

class WS2812Panel
{
private:
    CRGB *ledsPanel;
    FastLED_NeoMatrix *matrix;

    unsigned long previousMillis = 0;

public:
    WS2812Panel();
    void show();
    void drawFrame(Frame frame);
    void eraseScreen();
    void showTime(String timeString);
    void showCountdown(int countdownValue);
    void tick();
};