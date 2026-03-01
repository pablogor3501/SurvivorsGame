// Player.h
// #pragma once Or: #ifndef MYCLASS_H #define MYCLASS_H ... #endif
#ifndef PLAYER_H 
#define PLAYER_H 

#include <string>  // Include needed headers
#include "Entity.h"

class Player : public Entity 
{
public:
    Player(float x, float y);

    void handleInput(const Uint8* keyboardState);
    void update(float deltaTime) override;
    void render(SDL_Renderer *renderer, const Camera &camera);
};
#endif