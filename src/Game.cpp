//Game.cpp

#include <SDL2/SDL.h>
#include <iostream>
#include "Player.h"
#include "Camera.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Survivors Movement Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cout << "Window could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
    {
        std::cout << "Renderer could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // ---------------------------
    // Create game objects
    // ---------------------------

    Player player(0.0f, 0.0f);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    // ---------------------------
    // Game Loop
    // ---------------------------

    while (running)
    {
        // ---- Delta Time ----
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // ---- Events ----
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // ---- Input ----
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
        player.handleInput(keyboardState);

        // ---- Update ----
        player.update(deltaTime);
        camera.follow(player);

        // ---- Render ----
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        // Draw a simple grid for movement visualization
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

        for (int x = -2000; x <= 2000; x += 64)
        {
            float screenX = x - camera.position.x + SCREEN_WIDTH / 2;

            SDL_RenderDrawLineF(
                renderer,
                screenX, 0,
                screenX, SCREEN_HEIGHT
            );
        }

        for (int y = -2000; y <= 2000; y += 64)
        {
            float screenY = y - camera.position.y + SCREEN_HEIGHT / 2;

            SDL_RenderDrawLineF(
                renderer,
                0, screenY,
                SCREEN_WIDTH, screenY
            );
        }

        // Draw player (white)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        player.render(renderer, camera);

        SDL_RenderPresent(renderer);
    }

    // ---------------------------
    // Cleanup
    // ---------------------------

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}