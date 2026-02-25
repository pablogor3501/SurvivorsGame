#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Tile.h"
#include "TextureLoader.h"
#include "PerlinNoise.h"

class World
{
public:
    World(int width, int height, std::vector<SDL_Texture*> textureLoader);

    void render(SDL_Renderer* renderer, float camX, float camY, int screenWidth, int screenHeight);
    
private:
    int width;
    int height;
    std::vector<Tile> tiles;
    PerlinNoise noise;
    SDL_Texture* pickTexture(double value, std::vector<SDL_Texture*>);  // Picks texture based on Perlin noise value
    SDL_Texture* deepWaterTexture;
    SDL_Texture* waterTexture;
    SDL_Texture* shallowTexture;
    SDL_Texture* sandTexture;
    SDL_Texture* grassTexture;
    SDL_Texture* mountainTexture;
};

#endif // WORLD_H