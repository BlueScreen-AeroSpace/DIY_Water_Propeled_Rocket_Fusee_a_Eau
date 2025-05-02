#include "Animation/Frame.h"

Frame::Frame(uint16_t duration)
{
    this->duration = duration;
}

uint16_t Frame::getDuration() const
{
    return duration;
}

void Frame::addPixel(Pixel pixel)
{
    pixels.push_back(pixel);
}

std::vector<Pixel> &Frame::getPixels()
{
    return pixels;
}
