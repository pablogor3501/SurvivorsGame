#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>  // for sin, cos, log, M_PI


#include "Player.h"
#include "Camera.h"
#include "World.h"
#include "Enemy.h"

const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* argv[])
{
    // ─────────────────────────────────────────
    // SDL Init
    // ─────────────────────────────────────────
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Perlin Tile World",
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

    // ─────────────────────────────────────────
    // Game Objects
    // ─────────────────────────────────────────
    Player player(0.0f, 0.0f);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 10'000; ++i)
    {
        float x = (rand() % 2'000) - 1'000;  // random world position
        float y = (rand() % 2'000) - 1'000;
        enemies.emplace_back(x, y);
    }

    // 100x100 tiles centered around (0,0)  
    World world(100, 100);

    bool running = true;
    Uint32 lastTime = SDL_GetTicks();

    // ─────────────────────────────────────────
    // Game Loop
    // ─────────────────────────────────────────
    while (running)
    {
        // ---- Delta Time ----
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1'000.0f;
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
        for (auto& enemy : enemies)
        {
            enemy.handleMovement();     // pick random direction/speed
            enemy.update(deltaTime);    // move
        }
        player.update(deltaTime);
        camera.follow(player);

        // ─────────────────────────────────────────
        // Render
        // ─────────────────────────────────────────
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        // Render world (camera offset corrected for centered camera)
        float camOffsetX = camera.position.x - SCREEN_WIDTH  / 2;
        float camOffsetY = camera.position.y - SCREEN_HEIGHT / 2;

        world.render(renderer, camOffsetX, camOffsetY);

        // Render player (drawn centered via camera logic)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        player.render(renderer, camera);

        // Render Enemies
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (auto& enemy : enemies)
        {
            enemy.render(renderer, camera);
        }


        SDL_RenderPresent(renderer);
    }

    // ─────────────────────────────────────────
    // Cleanup
    // ─────────────────────────────────────────
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}