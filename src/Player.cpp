// Player.cpp
#include "Player.h"
#include "Camera.h"

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

void Player::render(SDL_Renderer* renderer, const Camera& camera) 
{

    // Render player (drawn centered via camera logic)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect playerRect;

    playerRect.x = position.x - camera.position.x + camera.screenWidth / 2;
    playerRect.y = position.y - camera.position.y + camera.screenHeight / 2;
    playerRect.w = width;
    playerRect.h = height;
    
    SDL_RenderFillRectF(renderer, &playerRect);
    
}