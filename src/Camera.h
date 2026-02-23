#ifndef CAMERA_H 
#define CAMERA_H 

#include "Entity.h"

class Camera 
{
public:
    Vec2 position;

    int screenWidth;
    int screenHeight;

    Camera(int w, int h);

    void follow(const Entity& target);
};

#endif