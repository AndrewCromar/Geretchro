#pragma once

#include "core/component.h"
#include "core/math/vectors.h"

class Rigidbody : public Component
{
public:
    enum class BodyType
    {
        Static,
        Dynamic
    };

    struct RigidbodySettings
    {
        BodyType bodyType = BodyType::Dynamic;

        float mass = 1.0f;
        float gravityScale = 1.0f;
    };

    RigidbodySettings settings;
    Math::Vector2 velocity;
    bool grounded = false;

    virtual ~Rigidbody() = default;
};