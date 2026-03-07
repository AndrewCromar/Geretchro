#pragma once
#include "collider.h"
#include "core/gameObject.h"
#include "core/math/vectors.h"

class BoxCollider : public Collider
{
public:
    float width = 10;
    float height = 10;

    Math::Vector4 getBoundingBox() const override
    {
        return {
            gameObject->transform->position.x,
            gameObject->transform->position.y,
            width,
            height
        };
    }
};