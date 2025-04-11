#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
private:
    std::vector<Frame> frames;
    int currentFrameIndex = 0;

public:
    Animation();
    void addFrame(Frame newFrame);
    int getCurrentFrameIndex();
    void setCurrentFrameIndex(int index);
};