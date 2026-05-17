#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
    Texture();
    Texture(SDL_Renderer* r);
    ~Texture();

    bool loadFromFile(std::string p);
    void free();
    void render(int x, int y);
    void render(int x, int y, SDL_Rect* );

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    int width;
    int height;
    bool animated;
};

#endif