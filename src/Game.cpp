/*
*  Game.cpp
*/

// ─────────────────────────────────────────
// Including Standard Libraries
// ─────────────────────────────────────────
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>  // for sin, cos, log, M_PI
#include <vector>
#include <filesystem>
// ─────────────────────────────────────────
// Including Custom Classes
// ─────────────────────────────────────────
#include "Player.h"
#include "Camera.h"
#include "World.h"
#include "Enemy.h"
#include "TextureLoader.h"

// ─────────────────────────────────────────
// Globals
// ─────────────────────────────────────────
// Variables
const int SCREEN_WIDTH  = 1280;
const int SCREEN_HEIGHT = 720;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
std::vector<SDL_Texture*> textures;

// Functions
SDL_Texture* loadTexture( std::string path );

bool init();
bool loadMedia();
void close();
// Alias
namespace fs = std::filesystem;

bool init()
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
    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }
   
    window = SDL_CreateWindow(
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

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED// | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer)
    {
        std::cout << "Renderer could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    return 0;
}

void close()
{
    // ─────────────────────────────────────────
    // Cleanup
    // ─────────────────────────────────────────
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
	renderer = NULL;
	//Free loaded image
	SDL_DestroyTexture( texture );
    texture = NULL;
    SDL_Quit();
}



int main(int argc, char* argv[])
{
    if (init() < 0)
    {
        std::cout << "Error on Initialization" << std::endl;
        return -1;
    }
    
    // Initialize the texture loader
    TextureLoader textureLoader(renderer);

    // Load textures
    std::string path = "assets/textures/";
    for (const auto & entry : fs::directory_iterator(path))
    {    
        std::cout << entry.path() << std::endl;
        textures.push_back(textureLoader.loadTexture(entry.path().string()));
    }

    // ─────────────────────────────────────────
    // Game Objects
    // ─────────────────────────────────────────
    Player player(0.0f, 0.0f);
    Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    std::vector<Enemy> enemies;
    for (int i = 0; i < 0'100; ++i)
    {
        float x = (rand() % 2'000) - 1'000;  // random world position
        float y = (rand() % 2'000) - 1'000;
        enemies.emplace_back(x, y);
    }

    // 100x100 tiles centered around (0,0)  
    World world(1'000, 1'000, textures);  // Pass the texture loader to the World constructor

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
        std::cout << "Time: " << int(1/deltaTime) << "fps" << std::endl;

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
        
        world.render(renderer, camOffsetX, camOffsetY, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        
        player.render(renderer, camera);

        // Render Enemies
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (auto& enemy : enemies)
        {
            enemy.render(renderer, camera);
        }

        SDL_RenderPresent(renderer);
    }

    close();

    return 0;
}