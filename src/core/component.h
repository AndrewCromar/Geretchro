#pragma once

class GameObject;

class Component
{
public:
    GameObject* gameObject = nullptr;
    
        virtual ~Component() {}

    virtual void start() {}
    virtual void update(float dt) {}
    virtual void draw() {}
};