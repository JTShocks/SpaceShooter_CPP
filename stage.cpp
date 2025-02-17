#include "stage.h"
#include "common.h"
#include "draw.h"
using namespace std;

Stage stage;
Entity* player;

SDL_Texture* bulletTexture;
SDL_Texture* enemyTexture;
SDL_Texture* enemyBulletTexture;

int enemySpawnTimer = 0;
int stageResetTimer = 0;

static void initPlayer()
{
	player = new Entity();
	stage.fighterTail->next = player;
	stage.fighterTail = player;


	player->position = glm::vec2(100, 100);
	player->texture = loadTexture("Sprites/player.png");
	player->side = PLAYER_SIDE;
	player->health = 1;
	SDL_QueryTexture(player->texture, NULL, NULL, &player->width, &player->height);
	

}

static void fireAlienBullet(Entity* e)
{
	Entity* bullet = new Entity();
	stage.bulletTail->next = bullet;
	stage.bulletTail = bullet;

	bullet->position = e->position;
	bullet->deltaPosition[0] = -ALIEN_BULLET_SPEED;
	bullet->health = 1;
	bullet->texture = enemyBulletTexture;
	bullet->width = 16;
	bullet->height = 8;
	bullet->side = ALIEN_SIDE;

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);
	bullet->position[1] += (e->height / 2);

	//Frames before firing again
	e->reload = (rand()% FPS*2);
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
	bullet->width = 16;
	bullet->height = 8;
	bullet->side = PLAYER_SIDE;

	SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->width, &bullet->height);
	bullet->position[1] += (player->height / 2);

	//Frames before firing again
	player->reload = 8;
}

static bool bulletHitFighter(Entity* b)
{
	Entity* e;
	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e->side != b->side && collision(b->position[0], b->position[1], b->width, b->height, e->position[0], e->position[1], e->width, e->height))
		{
			b->health = 0;
			e->health = 0;
			return true;
		}
	}
	return false;
}

static void doPlayer(void)
{
	if (player != NULL)
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

		if (bulletHitFighter(b) || b->position[0] < -b->width|| b->position[1] < -b->height || b->position.x > SCREEN_WIDTH ||b->position.y > SCREEN_HEIGHT)
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
		if (e != player && (e->position[0] < -e->width))
		{
			e->health = 0;
		}

		if (e->health == 0)
		{
			if (e == player)
			{
				player = NULL;
			}

			if (e == stage.fighterTail)
			{
				stage.fighterTail = prev;
			}
			//Updating the chain of currently loaded fighters and freeing space for new fighters
			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

static void doEnemies(void)
{
	Entity* e;
	for (e = stage.fighterHead.next; e != NULL; e = e->next)
	{
		if (e != player && player != NULL && --e->reload <= 0)
		{
			fireAlienBullet(e);
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
		enemy->width = 32;
		enemy->height = 32;
		enemy->side = ALIEN_SIDE;
		enemy->reload = FPS * (1 + (rand() % 3));
		SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->width, &enemy->height);
		enemy->health = 1;

		//Setting the velocity vector
		//Random speed moving to the left, since they spawn on the right
		enemy->deltaPosition[0] = -(2 + (rand() % 4));

		//Resetting the spawn timer in frames
		//Enemies will spawn at least every 30 seconds.
		enemySpawnTimer = 30 + (rand() % 60);

	}
}

static void clipPlayer(void)
{
	if (player != NULL)
	{
		if (player->position[0] < 0)
		{
			player->position[0] = 0;
		}
		if (player->position[1] < 0)
		{
			player->position[1] = 0;
		}
		if (player->position[0] > SCREEN_WIDTH/2)
		{
			player->position[0] = SCREEN_WIDTH / 2;
		}
		if (player->position[1] > SCREEN_HEIGHT - player->height)
		{
			player->position.y = SCREEN_HEIGHT - player->height;
		}
	}
}

//Resetting the game after the player dies
static void resetStage(void)
{
	Entity* e;
	//Go through all the fighters and free them from memory
	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}
	//Go through all the bullets and free them from memory
	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}

	//Reinitialize the stage and player
	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	enemySpawnTimer = 0;
	stageResetTimer = FPS * 2;

}
static void logic(void)
{
	doPlayer();
	doFighters();
	doBullets();
	spawnEnemies();
	doEnemies();
	clipPlayer();

	if (player == NULL && --stageResetTimer <= 0)
	{
		resetStage();
	}
}



static void drawPlayer()
{
	
	//Draw the player sprite
	if (player != NULL) //Safety for when the player dies it doesn't crash
	{
		blit(player->texture, player->position.x, player->position.y);
	}

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

	bulletTexture = loadTexture("Sprites/player_bullet.png");
	enemyBulletTexture = loadTexture("Sprites/player_bullet.png");
	enemyTexture = loadTexture("Sprites/player.png");

	enemySpawnTimer = 0;

	resetStage();

}