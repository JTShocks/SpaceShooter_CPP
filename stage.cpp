#include "stage.h"
#include "common.h"
#include "draw.h"
using namespace std;

Stage stage;
Entity* player;

SDL_Texture* bulletTexture;
SDL_Texture* enemyTexture;
SDL_Texture* enemyBulletTexture;

int enemySpawnTimer;
int stageResetTimer;

static void initPlayer()
{
	player = new Entity();
	stage.fighterTail->next = player;
	stage.fighterTail = player;


	player->position = glm::vec2(100, 100);
	player->texture = loadTexture("Sprites/player.png");
	player->side = PLAYER_SIDE;
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

		if (bulletHitFighter(b) || b->position[0] > SCREEN_WIDTH)
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
		if (e != player && (e->position[0] < -e->width || e->health == 0))
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

		prev = e;
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
	blit(player->texture, player->position[0],player->position[1]);
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

static void resetStage(void)
{
	Entity* e;
	while (stage.fighterHead.next)
	{
		e = stage.fighterHead.next;
		stage.fighterHead.next = e->next;
		free(e);
	}

	while (stage.bulletHead.next)
	{
		e = stage.bulletHead.next;
		stage.bulletHead.next = e->next;
		free(e);
	}

	stage.fighterTail = &stage.fighterHead;
	stage.bulletTail = &stage.bulletHead;

	initPlayer();

	enemySpawnTimer = 0;
	stageResetTimer = FPS * 2;

}


void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;



	bulletTexture = loadTexture("Sprites/player_bullet.png");
	enemyBulletTexture = loadTexture("Sprites/player_bullet.png");
	enemyTexture = loadTexture("Sprites/player.png");



}