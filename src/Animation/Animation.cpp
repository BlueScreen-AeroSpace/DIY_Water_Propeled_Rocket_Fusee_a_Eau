#include "Animation/Animation.h"

Animation::Animation()
{
    ;
}

void Animation::addFrame(Frame frame)
{
    this->frames.push_back(frame);
}

int Animation::getCurrentFrameIndex()
{
    return currentFrameIndex;
}

void Animation::setCurrentFrameIndex(int index)
{
    this->currentFrameIndex = index;
}