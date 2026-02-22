#include "mainMenu.h"

MainMenu::MainMenu(std::string t, int w, int h)
{
    title = t;
    width = w;
    height = h;
}

void MainMenu::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if(window == NULL)
    {
        SDL_Log("No se pudo crear la ventana: %s", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
    {
        SDL_Log("No se pudo crear el renderer: %s", SDL_GetError());
        return;
    }
}

void MainMenu::load()
{
    buttons[0] = Button(500, 500);
}

void MainMenu::update()
{
    SDL_Event e;
    SDL_Rect temp_b;
    int temp_c = 0xFF;
    while(true)
    {
        SDL_PollEvent(&e);

        if(e.type == SDL_QUIT)
        {
            break;
        }
        
        for(int i = 0; i < NUM_BUTTONS_MENU; i++)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            switch (e.type)
            {
            case SDL_MOUSEBUTTONUP:
                if (x >= buttons[i].position.x && x <= buttons[i].position.x + width &&
                    y >= buttons[i].position.y && y <= buttons[i].position.y + height)
                {
                    temp_c = temp_c ^ 0xFF; // Cambia el color del botón al hacer clic
                }
                break;
            
            default:
                break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        for(int i = 0; i < NUM_BUTTONS_MENU; i++)
        {
            temp_b = { buttons[i].position.x, buttons[i].position.y, BUTTON_WIDTH, BUTTON_HEIGHT };
            SDL_SetRenderDrawColor(renderer, 0x00, temp_c, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &temp_b);
        }
        
        SDL_RenderPresent(renderer);
    }
}

void MainMenu::close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    SDL_Quit();
}