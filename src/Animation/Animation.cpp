#include "Animation/Animation.h"

Animation::Animation()
{
    ;
}

void Animation::addFrame(Frame frame)
{
    this->frames.push_back(frame);
}

const Frame* Animation::getFrame(int index)
{
    if (index < 0 || index >= this->frames.size())
    {
        return nullptr;
    }

    return &frames[index];
}

void Animation::setName(const String &name)
{
    this->name = name;
}

const String& Animation::getName() const
{
    return name;
}

int Animation::getCurrentFrameIndex()
{
    return currentFrameIndex;
}

void Animation::setCurrentFrameIndex(int index)
{
    if (index >= 0 && index < frames.size())
    {
        currentFrameIndex = index;
    }
}

const std::vector<Frame> &Animation::getFrames() const
{
    return frames;
}