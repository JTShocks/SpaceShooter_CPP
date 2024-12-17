#include "draw.h"
#include "common.h"
#include "SDL_image.h"

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTexture(char* filename)
{
	SDL_Texture* texture;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);
	return texture;
}

void blit(SDL_Texture* texture, int x, int y)
{
	SDL_Rect destination;
	destination.x = x;
	destination.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
	SDL_RenderCopy(app.renderer, texture, NULL, &destination);
}