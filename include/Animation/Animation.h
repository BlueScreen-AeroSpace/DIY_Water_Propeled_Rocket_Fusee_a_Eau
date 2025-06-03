#pragma once
#include <vector>
#include "Frame.h"

class Animation
{
public:
    Animation();
    void addFrame(const Frame& newFrame);
    void setName(const String &name);
    const String& getName() const;
    int getCurrentFrameIndex();
    uint8_t getNumFrames() const;
    void setCurrentFrameIndex(int index);
    const std::vector<Frame>& getFrames() const;
    const Frame* getFrame(int index);
    String getNameNormalized() const;
private:
    String name;
    int currentFrameIndex = 0;
    std::vector<Frame> frames;
};