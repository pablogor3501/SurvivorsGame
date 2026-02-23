#include "Entity.h"
#include "Camera.h"

Entity::Entity(float x, float y, float w, float h)
    : position{ x, y }, velocity{ 0, 0 }, width(w), height(h) {}

void Entity::update(float deltaTime) 
{
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Entity::render(SDL_Renderer* renderer, const Camera& camera) 
{
    SDL_FRect rect;

    rect.x = position.x - camera.position.x + camera.screenWidth / 2;
    rect.y = position.y - camera.position.y + camera.screenHeight / 2;
    rect.w = width;
    rect.h = height;

    SDL_RenderFillRectF(renderer, &rect);
}