#include "main.h"
#include "SDL.h"
#include "memory"
#include <iostream>
#include "common.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include <cstdlib>

App app;
int main(int argc, char* argv[])
{
	memset(&app, 0, sizeof(App));

	initSDL();
	atexit(SDL_TLSCleanup);

	while (1)
	{
		prepareScene();
		doInput();
		presentScene();
		SDL_Delay(16);
	}
	return 0;
}
