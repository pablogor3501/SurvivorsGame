#include "button.h"

Button::Button()
{
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;
    buttonTexture = nullptr;
}

Button::Button(int x, int y, SDL_Renderer* renderer, std::string texturePath)
{
    position.x = x;
    position.y = y;
    width = BUTTON_WIDTH;
    height = BUTTON_HEIGHT;
    buttonTexture = Texture(renderer);
    buttonTexture.loadFromFile(texturePath);
}

Button::~Button()
{
    buttonTexture.free();
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;
}

void Button::handleEvent(SDL_Event& e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    switch (e.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (x >= position.x && x <= position.x + width &&
            y >= position.y && y <= position.y + height)
        {
            
        }
        break;
    
    default:
        break;
    }
}

void Button::render()
{
    if(&buttonTexture != nullptr)
    {
        buttonTexture.render(position.x, position.y);
    }
}
