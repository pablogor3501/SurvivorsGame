#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>

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
    std::vector<std::unique_ptr<Button>> buttons;
    std::string title;
    int width;
    int height;
};

#endif