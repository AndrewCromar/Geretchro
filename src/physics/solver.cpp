#include "solver.h"
#include "physics/components/collider.h"
#include "physics/components/rigidbody.h"
#include "core/gameObject.h"
#include "core/math/vectors.h"
#include <algorithm>
#include <iostream>

namespace Solver
{

PhysicsSettings settings;

static std::vector<::Collider*> colliders;

void registerCollider(::Collider* collider)
{
    colliders.push_back(collider);
}

void integrateVelocity(float dt);
void solveCollisions();
Math::Vector2 getBoundingBoxOverlap(const Math::Vector4& a, const Math::Vector4& b);
void moveObject(Math::Vector2 overlap, Collider* colA, Collider* colB);

void step(float dt)
{
    float subDt = dt / settings.iterations;
    for (int i = 0; i < settings.iterations; i++)
    {
        integrateVelocity(subDt);
        solveCollisions();
    }
}

void integrateVelocity(float dt)
{
    for (auto* collider : colliders)
    {
        Rigidbody* rb = collider->gameObject->rigidbody;
        if (!rb || rb->settings.bodyType == Rigidbody::BodyType::Static)
            continue;

        rb->grounded = false;
        rb->velocity.y += settings.gravity * rb->settings.gravityScale * dt;
        collider->gameObject->transform->position += rb->velocity * dt;
    }
}

void solveCollisions()
{
    for (int i = 0; i < (int)colliders.size(); i++)
    {
        auto boxA = colliders[i]->getBoundingBox();

        for (int j = i + 1; j < (int)colliders.size(); j++)
        {
            auto boxB = colliders[j]->getBoundingBox();

            Math::Vector2 overlap = getBoundingBoxOverlap(boxA, boxB);

            if (overlap.x > 0 && overlap.y > 0)
            {
                moveObject(overlap, colliders[i], colliders[j]);
            }
        }
    }
}

Math::Vector2 getBoundingBoxOverlap(const Math::Vector4& a, const Math::Vector4& b)
{
    // Check if boxes overlap at all
    float intersectX = std::min(a.x + a.z, b.x + b.z) - std::max(a.x, b.x);
    float intersectY = std::min(a.y + a.w, b.y + b.w) - std::max(a.y, b.y);

    if (intersectX <= 0 || intersectY <= 0)
        return {0, 0};

    // Minimum translation distance to separate on each axis
    float penX = std::min(a.x + a.z - b.x, b.x + b.z - a.x);
    float penY = std::min(a.y + a.w - b.y, b.y + b.w - a.y);

    return {penX, penY};
}

void moveObject(Math::Vector2 overlap, Collider* colA, Collider* colB)
{
    Rigidbody* rbA = colA->gameObject->rigidbody;
    Rigidbody* rbB = colB->gameObject->rigidbody;

    bool aIsStatic = (!rbA || rbA->settings.bodyType == Rigidbody::BodyType::Static);
    bool bIsStatic = (!rbB || rbB->settings.bodyType == Rigidbody::BodyType::Static);

    if (aIsStatic && bIsStatic)
        return;

    if (overlap.x < overlap.y)
    {
        // X-axis resolution
        float sign = (colA->gameObject->transform->position.x < colB->gameObject->transform->position.x) ? -1.0f : 1.0f;

        if (aIsStatic)
        {
            colB->gameObject->transform->position.x -= sign * overlap.x;
            if (rbB) rbB->velocity.x = 0;
        }
        else if (bIsStatic)
        {
            colA->gameObject->transform->position.x += sign * overlap.x;
            if (rbA) rbA->velocity.x = 0;
        }
        else
        {
            float half = overlap.x / 2.0f;
            colA->gameObject->transform->position.x += sign * half;
            colB->gameObject->transform->position.x -= sign * half;
        }
    }
    else
    {
        // Y-axis resolution
        float sign = (colA->gameObject->transform->position.y < colB->gameObject->transform->position.y) ? -1.0f : 1.0f;

        if (aIsStatic)
        {
            colB->gameObject->transform->position.y -= sign * overlap.y;
            if (rbB)
            {
                rbB->velocity.y = 0;
                if (sign > 0) rbB->grounded = true;
            }
        }
        else if (bIsStatic)
        {
            colA->gameObject->transform->position.y += sign * overlap.y;
            if (rbA)
            {
                rbA->velocity.y = 0;
                if (sign < 0) rbA->grounded = true;
            }
        }
        else
        {
            float half = overlap.y / 2.0f;
            colA->gameObject->transform->position.y += sign * half;
            colB->gameObject->transform->position.y -= sign * half;
            if (rbA) rbA->velocity.y = 0;
            if (rbB) rbB->velocity.y = 0;
        }
    }
}

}
