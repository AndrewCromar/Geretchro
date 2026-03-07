#pragma once

#include <functional>
#include "core/component.h"

class Sprite : public Component
{
public:
    std::function<void()> drawFunction;

    void draw() override
    {
        if (drawFunction)
            drawFunction();
    }
};