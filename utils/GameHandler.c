#include "Enemy.h"
#include "Player.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

typedef struct {
	int curRound;
	Enemy enemies[50];
	int enemiesCount;
	Player* player;
	Sprite sprite;
} GameHandler;

void HandleNewRound(GameHandler* game) {
	int newEnemiesCount = game->curRound * 5 > 50 ? 50 : game->curRound * 5;

	game->enemiesCount = newEnemiesCount;
	printf("Enemy count: %i\n", newEnemiesCount);
	for(int i = 0; i < newEnemiesCount; i++) {
		Enemy newEnemy = {
			.isAlive = 1,
			.pos = {256, 256},
			.rect = {256, 256, 16, 16},
			.sprite = CreateSprite("assets/img/zombie.png", 16)
		};	
		game->enemies[i] = newEnemy;
	}
}

void CheckEnemies(GameHandler* game) {
	int isAnyAlive = 0;
	for(int i = 0; i < game->enemiesCount; i++) {
		if(game->enemies[i].isAlive == 1) {
			isAnyAlive = 1;
		}
	}
	if(isAnyAlive == 1) {
		
	} else {
		game->curRound++;
		HandleNewRound(game);
	}
}

void UpdateEnemy(Enemy* enemy, GameHandler* game) {
	enemy->pos = Vector2MoveTowards(enemy->pos, game->player->pos, 1);
	enemy->rect.x = enemy->pos.x;
	enemy->rect.y = enemy->pos.y;
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
		DrawTextureRec(game->enemies[i].sprite.texture, game->enemies[i].sprite.mask, game->enemies[i].pos, WHITE);	
	}
}
