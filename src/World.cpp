#include "World.h"

World::World(int width, int height, std::vector<SDL_Texture*> textures)
    : width(width), height(height), noise(2001)
{

    // Create the world tiles based on Perlin noise values
    double freq = 0.05;
    int depth = 4;

    for (int y = -height; y < height; y++)
    {
        for (int x = -width; x < width; x++)
        {
            double value = noise.perlin2D(x, y, freq, depth);
            SDL_Texture* texture = pickTexture(value, textures);
            tiles.emplace_back(x, y, texture);
        }
    }
}

// Choose the texture based on the Perlin noise value
SDL_Texture* World::pickTexture(double value, std::vector<SDL_Texture*> textures)
{
    if (value < 0.3)      return textures[0];    // deep water
    else if (value < 0.4) return textures[1];        // water
    else if (value < 0.5) return textures[2];      // shallow
    else if (value < 0.6) return textures[3];        // sand
    else if (value < 0.75) return textures[4];      // grass
    else                  return textures[5];   // mountain
}

void World::render(SDL_Renderer* renderer, float camX, float camY, int screenWidth, int screenHeight)
{
    for (auto& tile : tiles)
    {
        if (tile.isVisible(camX, camY, screenWidth, screenHeight))
        {
            tile.render(renderer, camX, camY);
        }
    }
}