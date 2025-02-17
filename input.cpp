#include "common.h"
#include "input.h"


void doInput(void)
{
	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				doKeyDown(&event.key);
				break;
			case SDL_KEYUP:
				doKeyUp(&event.key);
				break;
			default:
				break;
		}
	}
}
void doKeyDown(SDL_KeyboardEvent* event)
{

	if(event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 1;
	}

	/*if (event->repeat == 0)
	{
		//Movement
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.inputVector[1] = -1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.inputVector[1] = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.inputVector[0] = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app.inputVector[0] = -1;
		}
		//Shooting
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			app.isShooting = true;
		}
	}*/
}

void doKeyUp(SDL_KeyboardEvent* event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keyboard[event->keysym.scancode] = 0;
	}

	/*if (event->repeat == 0)
	{
		//Movement
		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			app.inputVector[1] = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			app.inputVector[1] = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			app.inputVector[0] = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			app.inputVector[0] = 0;
		}

		//Shooting
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			app.isShooting = false;
		}
	}*/
}