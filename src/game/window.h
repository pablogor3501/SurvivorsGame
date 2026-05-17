#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window
{
public:
    Window();
    ~Window();

    bool init(const char* t, int w, int h);
    void update();
    void close();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif