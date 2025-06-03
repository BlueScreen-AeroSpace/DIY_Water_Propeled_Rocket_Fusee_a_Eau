#pragma once
#include "Pixel.h"
#include <Arduino.h>
#include <vector>

class Frame
{
private:
    std::vector<Pixel> pixels;
public:
    Frame();
    void addPixel(const Pixel& pixel);
    const std::vector<Pixel> &getPixels() const;
    uint16_t getNumPixels() const;
};