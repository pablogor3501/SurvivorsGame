// Entity.h

// #pragma once Or: #ifndef MYCLASS_H #define MYCLASS_H ... #endif
#ifndef ENTITY_H 
#define ENTITY_H 

#include <SDL2/SDL.h>

struct Vec2 
{
    float x;
    float y;
};

class Camera;

class Entity 
{
public:
    Vec2 position;
    Vec2 velocity;

    float width;
    float height;
    
    int health;
    const int MAXHEALTH = 100;

    Entity(float x, float y, float w, float h);
    virtual ~Entity() = default;

    virtual void update(float deltaTime);
    virtual void render(SDL_Renderer* renderer, const Camera& camera);
};

#endif