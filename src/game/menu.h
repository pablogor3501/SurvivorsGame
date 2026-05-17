#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <vector>

#include "button.h"

class Menu
{
public:
    Menu();
    ~Menu();

    Menu(SDL_Renderer* r, SDL_Window* w);

    void init();
    void load();
    void update();
    void close();

private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    std::vector<Button> buttons;
    SDL_Texture* background;
};

class MainMenu : public Menu
{
public:
    MainMenu(SDL_Renderer* r, SDL_Window* w);
};

#endif