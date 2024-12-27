#pragma once
#include "SDL.h"
#include "glm/glm.hpp"
#include "defs.h"
using namespace std;
//Container for structs
struct Mouse {
	//specifically using ints to be compatible with SDL functions
	int x;
	int y;
}; //Use this for referencing the mouse

struct Delegate{
	void(*logic)(void);
	void(*draw)(void);
};
struct App {
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mouse mouse;

	//Logic and draws
	Delegate delegate;

	int keyboard[MAX_KEYBOARD_KEYS];
	//Directions
	bool isMoving;
	glm::vec2 inputVector;

	bool isShooting;
}; //Use this for referencing everything in the app as it is running

struct Entity {

	int side;
	glm::vec2 position;
	glm::vec2 deltaPosition;
	//Determining area of collision
	int width;
	int height;

	int health;
	int reload;
	SDL_Texture* texture;

	//Linked list for chain of entities
	Entity* next;
};
struct Stage {
	//Details the effects of the stage elements
	Entity fighterHead, *fighterTail;
	Entity bulletHead, *bulletTail;
};



