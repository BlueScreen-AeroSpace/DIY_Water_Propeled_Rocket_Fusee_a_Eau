#pragma once
#include "Animation.h"

class AnimationSerializer
{
public:
    static Animation deserialize(const uint8_t* animationBytes, uint16_t offset);
    static const uint8_t* serialize(const Animation& animation, size_t& outLength);  
};