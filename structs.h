#pragma once

//Container for structs
typedef struct {
	int x;
	int y;
} Mouse; //Use this for referencing the mouse

typedef struct {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mouse mouse;
} App; //Use this for referencing everything in the app as it is running



