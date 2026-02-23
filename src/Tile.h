// Tile.h

#ifndef TILE_H 
#define TILE_H 
#include <SDL2/SDL.h>

const int TILE_SIZE = 64;

class Tile
{
public:
    Tile(int gridX, int gridY, SDL_Color color);

    void render(SDL_Renderer* renderer, float camX, float camY);

private:
        int x, y;          // grid position
        SDL_Color color;
};

#endif