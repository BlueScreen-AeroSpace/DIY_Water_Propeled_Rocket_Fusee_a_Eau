#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
    Animation();
    void addFrame(Frame newFrame);
    void setName(const String &name);
    const String& getName() const;
    int getCurrentFrameIndex();
    void setCurrentFrameIndex(int index);
    const std::vector<Frame>& getFrames() const;
    const Frame* getFrame(int index);
private:
    String name;
    int currentFrameIndex = 0;
    std::vector<Frame> frames;
};