// World.h
#ifndef WORLD_H 
#define WORLD_H 
#include <vector>
#include "Tile.h"
#include "PerlinNoise.h"

class World
{
public:
    World(int width, int height);

    void render(SDL_Renderer* renderer, float camX, float camY);

private:
    int width;
    int height;

    std::vector<Tile> tiles;
    PerlinNoise noise;

    SDL_Color pickColor(double value);
};

#endif