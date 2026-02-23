// Player.cpp
#include "Player.h"
#include <SDL2/SDL.h>

Player::Player(float x, float y)
    : Entity(x, y, 32, 32) {}

void Player::handleInput(const Uint8* keyboardState) 
{
    velocity = {0, 0};

    float speed = 200.0f;

    if (keyboardState[SDL_SCANCODE_W]) velocity.y = -speed;
    if (keyboardState[SDL_SCANCODE_S]) velocity.y =  speed;
    if (keyboardState[SDL_SCANCODE_A]) velocity.x = -speed;
    if (keyboardState[SDL_SCANCODE_D]) velocity.x =  speed;
}

void Player::update(float deltaTime) {
    Entity::update(deltaTime);
}
