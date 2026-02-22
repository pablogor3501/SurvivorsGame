#include "button.h"

Button::Button()
{
    position.x = 0;
    position.y = 0;
    width = 0;
    height = 0;
}

Button::Button(int x, int y)
{
    position.x = x;
    position.y = y;
    width = BUTTON_WIDTH;
    height = BUTTON_HEIGHT;
}

Button::~Button()
{
    // Limpieza de recursos si es necesario
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
    // Lógica para renderizar el botón en la pantalla
}
