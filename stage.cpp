#include "stage.h"
#include "common.h"
#include "draw.h"

Stage stage;
Entity* player;

SDL_Texture* bulletTexture;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	bulletTexture = loadTexture("Sprites/player.png");

}

static void initPlayer()
{
	player = new Entity;
	memset(player, 0, sizeof(Entity));
	stage.fighterTail->next = player;
	stage.fighterTail = player;

	player->position = glm::vec2(100, 100);
	player->texture = loadTexture("Sprites/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);

}

static void logic(void)
{
	doPlayer();
	doBullets();
}

static void doPlayer(void)
{
	player->deltaPosition = glm::vec2(0, 0);

}
