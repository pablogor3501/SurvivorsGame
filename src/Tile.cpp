// Tile.cpp
#include "Tile.h"

Tile::Tile(int gridX, int gridY, SDL_Color color)
    : x(gridX), y(gridY), color(color)
{}

void Tile::render(SDL_Renderer* renderer, float camX, float camY)
{
    SDL_Rect rect;
    rect.x = x * TILE_SIZE - camX;
    rect.y = y * TILE_SIZE - camY;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}