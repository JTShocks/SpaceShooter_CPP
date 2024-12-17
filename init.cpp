#include "SDL.h"
#include "common.h"
#include <iostream>

using namespace std;


void initSDL(void)
{
	int rendererFlags= SDL_RENDERER_ACCELERATED, windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Couldn't initialize SDL: " << SDL_GetError << "\n" << endl;
		exit(1);
	}
	app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	
}