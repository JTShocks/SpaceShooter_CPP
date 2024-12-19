#include "main.h"
#include "SDL.h"
#include "memory"
#include <iostream>
#include "common.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include <cstdlib>
#include "stage.h"
using namespace std;

App app;
static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
int main(int argc, char* argv[])
{

	long then;
	float remainder;

	memset(&app, 0, (sizeof(App)));

	initSDL();
	
	atexit(cleanup);

	initStage();

	then = SDL_GetTicks();

	remainder = 0;

	while (1)
	{
		prepareScene();

		doInput();
		app.delegate.logic();

		app.delegate.draw();

		presentScene();
		
		capFrameRate(&then, &remainder);
	}
	return 0;
}



void cleanup()
{
	std::cout << "Cleaning up\n";
	SDL_DestroyWindow(app.window);
	app.window = NULL;
	SDL_DestroyRenderer(app.renderer);
	app.renderer = NULL;
	SDL_Quit();
}
