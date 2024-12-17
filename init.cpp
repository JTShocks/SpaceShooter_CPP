#include "common.h"
#include <iostream>
#include <cstdlib>
#include "init.h"
using namespace std;


void initSDL(void)
{
	int rendererFlags = SDL_RENDERER_ACCELERATED;
	int windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Couldn't initialize SDL: " << SDL_GetError << "\n" << endl;
		exit(1);
	}
	app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	
	if (!app.window)
	{
		cout << "Failed to open " << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << " window : " << SDL_GetError << "\n" << endl;
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	if (!app.renderer)
	{
		cout << "Failed to create renderer: " << SDL_GetError << "\n" << endl;
		exit(1);
	}

}