#include <SDL2/SDL.h>

#include <string>

#include "window.h"
#include "menu.h"

int main(int argc, char *argv[])
{
	const std::string TITLE = "DEV SURVIVORS";
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	Window window = Window();
	if (!window.init(TITLE.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT))
	{
		SDL_Log("No se pudo inicializar la ventana: %s", SDL_GetError());
		return 1;
	}

	window.update();

	window.close();

	return 0;
}