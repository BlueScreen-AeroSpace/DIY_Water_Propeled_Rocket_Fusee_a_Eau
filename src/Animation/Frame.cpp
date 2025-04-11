#include "Animation/Frame.h"

Frame::Frame(uint16_t duration)
{
    this->duration = duration;
}

uint16_t Frame::getDuration()
{
    return duration;
}

void Frame::addPixel(Pixel pixel)
{
    pixels.push_back(pixel);
}
