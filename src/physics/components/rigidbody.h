#pragma once

#include "core/component.h"

class Rigidbody : public Component
{
public:
    enum class BodyType
    {
        Static,
        Dynamic
    };

    struct RidigbodySettings
    {
        BodyType bodyType = BodyType::Dynamic;

        float mass = 1.0f;
        float gravityScale = 1.0f;
    };

    RidigbodySettings settings;

    virtual ~Rigidbody() = default;
};