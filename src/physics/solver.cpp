#include "solver.h"
#include "physics/components/collider.h"
#include "physics/components/boxCollider.h"
#include "core/math/vectors.h"

namespace Solver
{

static std::vector<::Collider*> colliders;

void registerCollider(::Collider* collider)
{
    colliders.push_back(collider);
}

struct Vector2
{
    float x;
    float y;
};

void solveCollisions();
Vector2 getBoundingBoxOverlap(const Math::Vector4& a, const Math::Vector4& b);
void moveObject(Vector2 overlap, Collider* colA, Collider* colB);

void step()
{
    solveCollisions();
}

void solveCollisions()
{
    for (const auto& collider : colliders)
    {
        auto boxA = collider->getBoundingBox();

        for (const auto& other : colliders)
        {
            if (collider == other)
                continue;

            auto boxB = other->getBoundingBox();

            Vector2 overlap = getBoundingBoxOverlap(boxA, boxB);

            if (overlap.x > 0 && overlap.y > 0)
            {
                moveObject(overlap, collider, other);
            }
        }
    }
}

Vector2 getBoundingBoxOverlap(const Math::Vector4& a, const Math::Vector4& b)
{
    float overlapX = std::max(0.0f, std::min(a.x + a.z, b.x + b.z) - std::max(a.x, b.x));
    float overlapY = std::max(0.0f, std::min(a.y + a.w, b.y + b.w) - std::max(a.y, b.y));

    return {overlapX, overlapY};
}

void moveObject(Vector2 overlap, Collider* colA, Collider* colB)
{
    if (overlap.x < overlap.y)
    {
        float halfOverlapX = overlap.x / 2.0f;

        if (colA->gameObject->transform->position.x < colB->gameObject->transform->position.x)
        {
            colA->gameObject->transform->position.x -= halfOverlapX;
            colB->gameObject->transform->position.x += halfOverlapX;
        }
        else
        {
            colA->gameObject->transform->position.x += halfOverlapX;
            colB->gameObject->transform->position.x -= halfOverlapX;
        }
    }
    else
    {
        float halfOverlapY = overlap.y / 2.0f;

        if (colA->gameObject->transform->position.y < colB->gameObject->transform->position.y)
        {
            colA->gameObject->transform->position.y -= halfOverlapY;
            colB->gameObject->transform->position.y += halfOverlapY;
        }
        else
        {
            colA->gameObject->transform->position.y += halfOverlapY;
            colB->gameObject->transform->position.y -= halfOverlapY;
        }
    }
}

}