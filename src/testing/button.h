#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "texture.h"

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

class Button
{
public:
    Button();
    Button(int x, int y, SDL_Renderer* renderer, std::string texturePath);
    ~Button();

    void handleEvent(SDL_Event& e);
    void render();

    SDL_Point getPosition() const { return position; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

//private:
    Texture buttonTexture;
    SDL_Point position;
    int width;
    int height;
};
#endif