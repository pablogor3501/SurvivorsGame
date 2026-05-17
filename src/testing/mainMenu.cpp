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
    buttons.push_back(std::make_unique<Button>(300, 300, renderer, "assets/button_test.bmp"));
}

void MainMenu::update()
{
    SDL_Event e;

    Texture texture = Texture(renderer);
    texture.loadFromFile("assets/button_test.bmp");
    SDL_Log("Entrando al bucle principal del menú");

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
            case SDL_MOUSEBUTTONDOWN:
                SDL_Log("Botón %d presionado", i);
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        buttons[0]->render();
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