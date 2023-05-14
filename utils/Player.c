#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "MapHandler.h"
#include "Bullet.h"

typedef struct {
	Vector2 pos;
	Vector2 acceleration;
	Vector2 prevPos;
	Rectangle rect;
	int animationCount;
	Sprite sprite;
	int bulletCount;
	Bullet bullets[50];
	int reloadCount;
} Player;

void CheckPlayerCollisions(Player* player, MapHandler mapHandler) {
	for(int i = 0; i < mapHandler.objectCount; i++) {
		if(CheckCollisionRecs(player->rect, mapHandler.objects[i].rect)) {
			player->pos = player->prevPos;
		}
	}
}

void AddBullet(Player* player, Vector2 dir) {
	printf("%i\n", player->reloadCount);
	if(player->reloadCount<15) {
		return;
	}
	player->reloadCount = 0;

	printf("Adding bullet at %i\n", player->bulletCount);
	player->bulletCount++;
	Bullet newBullet = {
		.direction = dir,
		.rect = {
			.height = 4,
			.width = 4,
			.x = player->pos.x,
			.y = player->pos.y
		},
		.isAlive = 1
	};
	player->bullets[player->bulletCount] = newBullet;
}

void UpdateBullets(Sprite sprite, Player* player) {
	for(int i = 0; i < player->bulletCount; i++) {
		Vector2 pos = {player->bullets[i].rect.x, player->bullets[i].rect.y};
		Vector2 mult = {2,2};
		Vector2 newPos = Vector2Add(pos, Vector2Multiply(player->bullets[i].direction, mult)); 
		player->bullets[i].rect.x = newPos.x;
		player->bullets[i].rect.y = newPos.y;
		if(player->bullets[i].isAlive == 1) {
			DrawTextureRec(sprite.texture, player->bullets[i].rect, pos, WHITE);
		}
	}
}

void UpdatePlayer(Player* player, MapHandler mapHandler) {
	if(player->reloadCount < 30)
		player->reloadCount++;

	if(player->acceleration.x == 0 && player->acceleration.y == 0) {
		player->sprite.curStep = 0;
	}
	if(player->acceleration.x != 0 || player->acceleration.y != 0) {
		player->animationCount++;
		if(player->animationCount % 4 == 0) {
			player->sprite.curStep++;
			player->animationCount = 0;
		}
		if(player->sprite.curStep >= 4) {
			player->sprite.curStep = 0;
		}
	}
	player->prevPos = player->pos;
	player->pos = Vector2Add(player->pos, player->acceleration);
	player->rect.x = player->pos.x;
	player->rect.y = player->pos.y;
	CheckPlayerCollisions(player, mapHandler);
	UpdateSprite(&player->sprite);
}


