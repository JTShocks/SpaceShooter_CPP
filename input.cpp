#include "SDL.h"
#include "structs.h"

App app;

void doInput(void)
{
	SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
}