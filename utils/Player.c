#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "MapHandler.h"

typedef struct {
	Vector2 pos;
	Vector2 acceleration;
	Vector2 prevPos;
	Rectangle rect;
	Sprite sprite;
} Player;

void CheckPlayerCollisions(Player* player, MapHandler mapHandler) {
	for(int i = 0; i < mapHandler.objectCount; i++) {
		if(CheckCollisionRecs(player->rect, mapHandler.objects[i].rect)) {
			player->pos = player->prevPos;
		}
	}
}

void UpdatePlayer(Player* player, MapHandler mapHandler) {
	if(player->acceleration.x == 0 && player->acceleration.y == 0) {
		player->sprite.curStep = 0;
	}
	if(player->acceleration.x != 0 || player->acceleration.y != 0) {
		player->sprite.curStep++;
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


