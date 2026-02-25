#include "TextureLoader.h"
#include <SDL2/SDL_image.h>
#include <iostream>

TextureLoader::TextureLoader(SDL_Renderer* renderer)
    : m_renderer(renderer)
{
}

TextureLoader::~TextureLoader()
{
    for (SDL_Texture* tex : m_textures)
    {
        SDL_DestroyTexture(tex);
    }
}

SDL_Texture* TextureLoader::loadTexture(const std::string& path)
{
    SDL_Texture* newTexture = nullptr;
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
    {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
    if (!newTexture)
    {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }
    
    SDL_FreeSurface(loadedSurface);
    
    if (newTexture)
    {
        m_textures.push_back(newTexture);
    }
    
    return newTexture;
}

SDL_Texture* TextureLoader::getTexture(int index)
{
    if (index >= 0 && index < m_textures.size())
    {
        return m_textures[index];
    }
    return nullptr;
}