#pragma once

#include <functional>
#include "core/component.h"

class Sprite : public Component
{
public:
    std::function<void()> draw;
};