#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class TextureLoader
{
public:
    // Constructor
    TextureLoader(SDL_Renderer* renderer);
    
    // Destructor
    ~TextureLoader();
    
    // Loads a texture from a file path
    SDL_Texture* loadTexture(const std::string& path);
    
    // Returns the loaded texture
    SDL_Texture* getTexture(int index);
    
private:
    SDL_Renderer* m_renderer;
    std::vector<SDL_Texture*> m_textures;
};

#endif // TEXTURELOADER_H