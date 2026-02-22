#include <SDL2/SDL.h>

#include "mainMenu.h"

int main(int argc, char *argv[])
{
  const std::string TITLE = "DEV SURVIVORS";
  const int WINDOW_WIDTH = 1920;
  const int WINDOW_HEIGHT = 1080;

  MainMenu mainMenu(TITLE, WINDOW_WIDTH, WINDOW_HEIGHT);
  mainMenu.init();
  mainMenu.load();
  mainMenu.update();
  mainMenu.close();

  return 0;
}