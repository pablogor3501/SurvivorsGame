#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Texture
{
public:
    Texture();
    Texture(SDL_Renderer* renderer);
    ~Texture();

    bool loadFromFile(std::string path);
    void free();

    void render(int x, int y, SDL_Rect* textureRect = NULL);

//private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width;
    int height;
};

#endif