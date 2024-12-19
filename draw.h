#pragma once
#include "common.h"
#include "SDL_image.h"

void prepareScene(void);
void presentScene(void);
SDL_Texture* loadTexture(const char* filename);
void blit(SDL_Texture* texture, int x, int y);
