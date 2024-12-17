#include "draw.h"
#include "SDL.h"
#include "structs.h"

void prepareScene(void)
{
	SDL_SetRendererDrawColor(app.renderer, 96, 128, 255, 255);
}