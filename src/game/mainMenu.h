#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL2/SDL.h>
#include <string>

#include "button.h"

const int NUM_BUTTONS_MENU = 1;

class MainMenu
{
public:
    MainMenu(std::string t, int w, int h);
    void init();
    void load();
    void update();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Button buttons[NUM_BUTTONS_MENU];
    std::string title;
    int width;
    int height;
};

#endif