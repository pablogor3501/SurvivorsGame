#include "Tile.h"

Tile::Tile(int gridX, int gridY, SDL_Texture* texture)
    : x(gridX), y(gridY), m_texture(texture)
{}

void Tile::render(SDL_Renderer* renderer, float camX, float camY)
{
    SDL_Rect rect;
    rect.x = x * TILE_SIZE - camX;
    rect.y = y * TILE_SIZE - camY;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    // Render the texture
    SDL_RenderCopy(renderer, m_texture, nullptr, &rect);
}

// Method to check if the tile is visible within the camera bounds
bool Tile::isVisible(float camX, float camY, int screenWidth, int screenHeight) const
{
    // Calculate the tile's screen position
    int screenX = x * TILE_SIZE - camX;
    int screenY = y * TILE_SIZE - camY;

    // Check if the tile is within the screen's bounds
    return !(screenX + TILE_SIZE < 0 || screenX > screenWidth || screenY + TILE_SIZE < 0 || screenY > screenHeight);
}