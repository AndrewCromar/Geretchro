#pragma once

class GameObject;

class Component
{
public:
    GameObject* gameObject = nullptr;

    virtual void start() {}
    virtual void update(float dt) {}

    virtual ~Component() {}
};