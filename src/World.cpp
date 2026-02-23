// World.cpp

#include "World.h"

World::World(int width, int height)
    : width(width), height(height), noise(2001)
{
    double freq = 0.05;
    int depth = 4;

    for (int y = -height; y < height; y++)
    {
        for (int x = -width; x < width; x++)
        {
            double value = noise.perlin2D(x, y, freq, depth);
            SDL_Color col = pickColor(value);

            tiles.emplace_back(x, y, col);
        }
    }
}

SDL_Color World::pickColor(double value)
{
    if (value < 0.3)      return { 41, 54,111,255 };   // deep water
    else if (value < 0.4) return { 59, 93,201,255 };   // water
    else if (value < 0.5) return { 64,166,245,255 };   // shallow
    else if (value < 0.6) return {114,239,247,255 };   // sand
    else if (value < 0.75)return { 86,108,134,255 };   // grass
    else                  return {148,175,194,255 };   // mountain
}

void World::render(SDL_Renderer* renderer, float camX, float camY)
{
    for (auto& tile : tiles)
        tile.render(renderer, camX, camY);
}   