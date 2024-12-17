#pragma once
#include "SDL.h"
//Container for structs
struct Mouse {
	int x;
	int y;
}; //Use this for referencing the mouse

struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mouse mouse;
}; //Use this for referencing everything in the app as it is running

struct Entity {
	int x;
	int y;
	SDL_Texture* texture;
};



