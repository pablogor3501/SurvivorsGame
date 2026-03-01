// Enemy.cpp
#include "Enemy.h"
#include "Camera.h"
#include <SDL2/SDL.h>

Enemy::Enemy(float x, float y)
    : Entity(x, y, 32, 32) 
    {}


void Enemy::handleMovement() 
{
    velocity = {0, 0};
    // Select Random Speed
    float speed = ((float)rand() / (float)RAND_MAX) * 500.0f;;
    
    if (counter % 100 == 0)
    {
        // Select Random Direction
        choice = rand() % 4;
    }

    // Move in Selected Speed and Direction
    if (choice == 0) velocity.y = -speed;
    if (choice == 1) velocity.y =  speed;
    if (choice == 2) velocity.x = -speed;
    if (choice == 3) velocity.x =  speed;
    
    counter += 1;
}

void Enemy::update(float deltaTime) {
    Entity::update(deltaTime);
}

void Enemy::render(SDL_Renderer* renderer, const Camera& camera) 
{

    // Render player (drawn centered via camera logic)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect playerRect;

    playerRect.x = position.x - camera.position.x + camera.screenWidth / 2;
    playerRect.y = position.y - camera.position.y + camera.screenHeight / 2;
    playerRect.w = width;
    playerRect.h = height;
    
    SDL_RenderFillRectF(renderer, &playerRect);

    // Render player (drawn centered via camera logic)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_FRect basehealthRect;
    
    basehealthRect.x = position.x - camera.position.x + camera.screenWidth / 2;
    basehealthRect.y = (position.y - camera.position.y + camera.screenHeight / 2) + 32 + 5;
    basehealthRect.w = width;
    basehealthRect.h = 3;
     
    SDL_RenderFillRectF(renderer, &basehealthRect);

    // Render player (drawn centered via camera logic)
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_FRect healthRect;
    
    healthRect.x = position.x - camera.position.x + camera.screenWidth / 2;
    healthRect.y = (position.y - camera.position.y + camera.screenHeight / 2) + 32 + 5;
    healthRect.w = width * 0.75;
    healthRect.h = 3;
     
    SDL_RenderFillRectF(renderer, &healthRect);
}