#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool init()
{
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
    return false;
  }
  
  gWindow = SDL_CreateWindow(
    "Dev Survivors",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if(gWindow == NULL)
  {
    SDL_Log("No se pudo crear la ventana: %s", SDL_GetError());
    return false;
  }

  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

  if(gRenderer == NULL)
  {
    SDL_Log("No se pudo crear el renderer: %s", SDL_GetError());
    return false;
  }
  
  return true;
}

bool close()
{
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gRenderer = NULL;
  gWindow = NULL;

  SDL_Quit();
  
  return true;
}

int main(int argc, char *argv[])
{
  if(!init())
  {
    SDL_Log("Fallo al inicializar");
    return -1;
  }

  int posX = WINDOW_WIDTH / 2;
  int posY = WINDOW_HEIGHT / 2;
  
  bool quit = false;
  SDL_Event e;

  while(!quit)
  {
    while(SDL_PollEvent(&e) != 0)
    {
      if(e.type == SDL_QUIT)
      {
        quit = true;
      }
      else if(e.type == SDL_KEYDOWN)
      {
        switch(e.key.keysym.sym)
        {
          case SDLK_UP:
            posY -= 10;
            break;
          case SDLK_DOWN:
            posY += 10;
            break;
          case SDLK_LEFT:
            posX -= 10;
            break;
          case SDLK_RIGHT:
            posX += 10;
            break;
        }
      }
    }
    
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect fillRect = { posX, posY, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10 };
    SDL_RenderFillRect(gRenderer, &fillRect);
    
    SDL_RenderPresent(gRenderer);
  }

  if(!close())
  {
    SDL_Log("Fallo al cerrar");
    return -1;
  }
  return 0;
}