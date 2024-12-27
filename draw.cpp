#include "draw.h"
#include "common.h"
#include "SDL_image.h"
#include "stdlib.h"
using namespace std;

void prepareScene(void)
{
	SDL_SetRenderDrawColor(app.renderer, 55, 55, 55, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture* loadTexture(const char* filename)
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