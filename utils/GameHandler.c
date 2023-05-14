#include "Enemy.h"
#include "MapHandler.h"
#include "Player.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "SpawnLocation.h"

typedef struct {
	int curRound;
	Enemy enemies[50];
	int enemiesCount;
	Player* player;
	Sprite sprite;
	MapHandler* mapHandler;
	SpawnLocation spawns[4];
} GameHandler;

void HandleNewRound(GameHandler* game, SpawnLocation spawns[4]) {
	printf("newround %f, %f\n", spawns[0].pos.x, spawns[0].pos.y);
	printf("CurRound %i\n", game->curRound);
	int newEnemiesCount = game->curRound * 4 > 50 ? 50 : game->curRound * 4;
	game->enemiesCount = newEnemiesCount;
	printf("Enemy count: %i\n", newEnemiesCount);
	for(int i = 0; i < newEnemiesCount; i+=4) {
		for(int j = 0; j < 4; j++) {
			printf("Spawning enemy at %f, %f\n", spawns[j].pos.x, spawns[j].pos.y);
			Enemy newEnemy = {
				.isAlive = 1,
				.pos = spawns[j].pos,
				.prevPos = spawns[j].pos,
				.rect = {spawns[j].pos.x, spawns[j].pos.y, 16, 16},
				.sprite = CreateSprite("assets/img/zombie.png", 16)
			};	
			game->enemies[i+j] = newEnemy;
		}
	}
}

void CheckEnemies(GameHandler* game, SpawnLocation spawns[4]) {
	int isAnyAlive = 0;
	for(int i = 0; i < game->enemiesCount; i++) {
		if(game->enemies[i].isAlive == 1) {
			isAnyAlive = 1;
		}
	}
	if(isAnyAlive == 1) {
		
	} else {
		printf("No enemies left\n");
		game->curRound++;
		HandleNewRound(game, spawns);
	}
}

void UpdateEnemy(Enemy* enemy, GameHandler* game, MapHandler* mapHandler) {
	enemy->prevPos = enemy->pos;
	enemy->pos = Vector2MoveTowards(enemy->pos, game->player->pos, .5);

	enemy->rect.x = enemy->pos.x;
	enemy->rect.y = enemy->pos.y;

	for(int i = 0; i < game->player->bulletCount; i++) {
		if(enemy->isAlive != 0 && CheckCollisionRecs(enemy->rect, game->player->bullets[i].rect)) {
			enemy->isAlive = 0;
			game->player->bullets[i].isAlive = 0;
		}
	}

	for(int i = 0; i < mapHandler->objectCount; i++) {
		if(CheckCollisionRecs(enemy->rect, mapHandler->objects[i].rect)) {
			enemy->pos = enemy->prevPos;
		}
	}

	enemy->animationCount++;
	if(enemy->animationCount % 4 == 0) {
		enemy->sprite.curStep++;
		enemy->animationCount = 0;
	}
	if(enemy->sprite.curStep >= 8) {
		enemy->sprite.curStep = 0;
	}
	UpdateSprite(&enemy->sprite);
}

void DrawEnemies(GameHandler* game) {
	for(int i = 0; i < game->enemiesCount; i++) {
		if(game->enemies[i].isAlive == 1)
			DrawTextureRec(game->enemies[i].sprite.texture, game->enemies[i].sprite.mask, game->enemies[i].pos, WHITE);	
	}
}
