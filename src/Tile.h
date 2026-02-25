#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

const int TILE_SIZE = 64;

class Tile
{
public:
    Tile(int gridX, int gridY, SDL_Texture* texture);

    void render(SDL_Renderer* renderer, float camX, float camY);
    
    // Check if the tile is within the camera's visible area
    bool isVisible(float camX, float camY, int screenWidth, int screenHeight) const;

private:
    int x, y;                  // Grid position
    SDL_Texture* m_texture;    // Texture to render
};

#endif // TILE_H