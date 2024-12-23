#include "stage.h"
#include "common.h"
#include "draw.h"
using namespace std;

Stage stage;
Entity* player;

SDL_Texture* bulletTexture;
SDL_Texture* enemyTexture;

int enemySpawnTimer;

static void initPlayer()
{
	player = new Entity();
	stage.fighterTail->next = player;
	stage.fighterTail = player;


	player->position = glm::vec2(100, 100);
	player->texture = loadTexture("Sprites/player.png");
	SDL_QueryTexture(player->texture, NULL, NULL, &player->width, &player->height);
	

}

static void fireBullet()
{
	Entity* bullet = new Entity();
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->position = player->position;
	bullet->deltaPosition[0] = PLAYER_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = bulletTexture;
	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);
	bullet->position[1] += (player->height / 2) - (bullet->health / 2);

	//Frames before firing again
	player->reload = 8;
}

static void doPlayer(void)
{
	player->deltaPosition = glm::vec2(0, 0);

	if (player->reload > 0)
	{
		player->reload--;
	}

	if (app.keyboard[SDL_SCANCODE_DOWN])
	{
		player->deltaPosition[1] = PLAYER_SPEED;
	}
	if (app.keyboard[SDL_SCANCODE_UP])
	{
		player->deltaPosition[1] = -PLAYER_SPEED;
	}
	if (app.keyboard[SDL_SCANCODE_RIGHT])
	{
		player->deltaPosition[0] = PLAYER_SPEED;
	}
	if (app.keyboard[SDL_SCANCODE_LEFT])
	{
		player->deltaPosition[0] = -PLAYER_SPEED;
	}

	//Firing bullets
	if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0)
	{
		fireBullet();
	}

	player->position += player->deltaPosition;
}



//Controlling all the bullets. 
static void doBullets(void)
{
	//Active bullet and previous bullet
	Entity* b;
	Entity* previous;

	previous = &stage.bulletHead;

	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		b->position += b->deltaPosition;

		if (b->position[0] > SCREEN_WIDTH)
		{
			if(b == stage.bulletTail)
			{
				stage.bulletTail = previous;
			}

			previous->next = b->next;
			free(b);
			b = previous;
		}

		previous = b;
	}
}

static void doFighters(void)
{
	Entity* e, * prev;
	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		e->position += e->deltaPosition;

		//Handling when enemy goes off screen
		if (e != player && e->position[0] < -e->width)
		{
			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}

			//Updating the chain of currently loaded fighters and freeing space for new fighters
			prev->next = e->next;
			free(e);
			e = prev;
		}
	}
}

static void spawnEnemies()
{
	Entity* enemy;

	if (--enemySpawnTimer <= 0)
	{
		enemy = new Entity();
		stage.fighterTail->next = enemy;
		stage.fighterTail = enemy;

		//Assigning enemy values in struct
		enemy->position = glm::vec2(SCREEN_WIDTH, (rand() % SCREEN_HEIGHT));
		enemy->texture = enemyTexture;
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->width, &enemy->height);

		//Setting the velocity vector
		//Random speed moving to the left, since they spawn on the right
		enemy->deltaPosition[0] = -(2 + (rand() % 4));

		//Resetting the spawn timer
		enemySpawnTimer = 30 + (rand() % 60);

	}
}
static void logic(void)
{
	doPlayer();
	doFighters();
	doBullets();
	spawnEnemies();
}



static void drawPlayer()
{
	//Draw the player sprite
	blit(player->texture, player->position[0], player->position[1]);
}

static void drawBullets()
{
	Entity* b;
	for (b = stage.bulletHead.next; b != NULL; b = b->next)
	{
		blit(b->texture, b->position[0], b->position[1]);
	}
}

static void drawFighters(void)
{
	Entity* e;
	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		blit(e->texture, e->position[0], e->position[1]);
	}
}

//RENDERING 
static void draw(void)
{
	drawPlayer();
	drawBullets();
	drawFighters();
}


void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	bulletTexture = loadTexture("Sprites/player.png");
	enemyTexture = loadTexture("Sprites/player.png");

	enemySpawnTimer = 0;

}