// Enemy.h
// #pragma once Or: #ifndef MYCLASS_H #define MYCLASS_H ... #endif
#ifndef ENEMY_H 
#define ENEMY_H 

#include <string>  // Include needed headers
#include "Entity.h"

class Enemy : public Entity 
{
public:
    Enemy(float x, float y);
    
    // APAÑO
    int choice = rand() % 4;
    int counter = 0;
    

    void handleMovement();
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer, const Camera &camera);
};
#endif