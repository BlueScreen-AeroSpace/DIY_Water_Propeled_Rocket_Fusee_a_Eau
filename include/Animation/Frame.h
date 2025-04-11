#pragma once
#include "Pixel.h"
#include <Arduino.h>
#include <vector>

class Frame
{
private:
    std::vector<Pixel> pixels;
    int duration;

public:
    Frame(uint16_t duration);
    uint16_t getDuration();
    void addPixel(Pixel pixel);
};