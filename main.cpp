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
Entity player;
int main(int argc, char* argv[])
{
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));

	initSDL();
	player.position = glm::vec2(100, 100);
	player.texture = loadTexture("Sprites/player.png");

	atexit(cleanup);

	while (1)
	{
		prepareScene();
		doInput();
		blit(player.texture, player.position[0], player.position[1]);
		presentScene();

		player.position += glm::vec2(app.inputVector[0] * 4,app.inputVector[1] * 4);
		
		SDL_Delay(16);
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
