#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button
{
public:
    Button();
    Button(int x, int y);
    ~Button();
    void handleEvent(SDL_Event& e);
    void render();
//private:
    SDL_Point position;
    int width;
    int height;
};
#endif