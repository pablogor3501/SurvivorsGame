// Enemy.cpp
#include "Enemy.h"
#include <SDL2/SDL.h>

Enemy::Enemy(float x, float y)
    : Entity(x, y, 32, 32) 
    {
    }


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
