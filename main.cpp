#include "main.h"
#include "SDL.h"
#include "memory"
#include <iostream>
#include "common.h"
#include "init.h"
#include "draw.h"
#include "input.h"
#include <cstdlib>
using namespace std;

App app;
int main(int argc, char* argv[])
{
	memset(&app, 0, sizeof(App));

	initSDL();
	
	//TO:DO > Replace temp texture for bullet
	bullet.texture = loadTexture("Sprites/player.png");

	atexit(cleanup);

	while (1)
	{
		prepareScene();
		doInput();

		//Moving the player
		player.position += glm::vec2(app.inputVector[0] * 4, app.inputVector[1] * 4);
		player.position[0] = glm::clamp((int)player.position[0], 0, SCREEN_WIDTH-64);
		player.position[1] = glm::clamp((int)player.position[1], 0, SCREEN_HEIGHT-64);

		//Spawning the bullet
		if (app.isShooting && bullet.health == 0)
		{
			bullet.position = player.position;
			bullet.deltaPosition = glm::vec2(16, 0);
			bullet.health = 1;
		}

		//Moving the bullet across the screen
		bullet.position += bullet.deltaPosition;

		//Draw the player sprite
		blit(player.texture, player.position[0], player.position[1]);


		//What happens when the bullet goes off screen/ out of bounds
		if (bullet.position[0] > SCREEN_WIDTH)
		{
			bullet.health = 0;
		}
		if (bullet.health > 0)
		{
			//Draw bullet while it is alive
			blit(bullet.texture, bullet.position[0], bullet.position[1]);
		}

		presentScene();
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
