#pragma once
#include "SDL.h"
#include "glm/glm.hpp"
using namespace std;
//Container for structs
struct Mouse {
	//specifically using ints to be compatible with SDL functions
	int x;
	int y;
}; //Use this for referencing the mouse

struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mouse mouse;

	//Directions
	bool isMoving;
	glm::vec2 inputVector;

	bool isShooting;
}; //Use this for referencing everything in the app as it is running

struct Entity {
	glm::vec2 position;
	glm::vec2 deltaPosition;
	int health;
	SDL_Texture* texture;
};



