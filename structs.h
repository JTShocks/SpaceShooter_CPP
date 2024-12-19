#pragma once
#include "SDL.h"
#include "glm/glm.hpp"
using namespace std;
//Container for structs
struct Mouse {
	int x;
	int y;
}; //Use this for referencing the mouse

struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mouse mouse;

	//Directions
	bool hasMoveInput;
	glm::vec2 inputVector;
}; //Use this for referencing everything in the app as it is running

struct Entity {
	int x;
	int y;
	SDL_Texture* texture;
};



