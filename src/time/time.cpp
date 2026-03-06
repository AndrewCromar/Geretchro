#include <Arduino.h>
#include "time.h"

namespace Time
{
    unsigned long lastFrameTime = 0;
    float dt = 0.016f;
    float currentFps = 60.0f;

    void update()
    {
        unsigned long now = millis();

        dt = (now - lastFrameTime) / 1000.0f;

        if (dt > 0)
            currentFps = 1.0f / dt;

        lastFrameTime = now;
    }

    float deltaTime()
    {
        return dt;
    }

    float fps()
    {
        return currentFps;
    }
}