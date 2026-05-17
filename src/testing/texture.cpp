#include "texture.h"

Texture::Texture()
{
    texture = NULL;
    renderer = NULL;
    width = 0;
    height = 0;
}

Texture::Texture(SDL_Renderer* r)
{
    texture = NULL;
    renderer = r;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(std::string path)
{
    free();

    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
    {
        SDL_Log("No se pudo cargar la imagen: %s", SDL_GetError());
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if(texture == NULL)
    {
        SDL_Log("No se pudo crear la textura: %s", SDL_GetError());
        return false;
    }

    width = loadedSurface->w;
    height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    return true;
}

void Texture::free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::render(int x, int y, SDL_Rect* textureRect)
{
    SDL_Rect renderRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, textureRect, &renderRect);
}