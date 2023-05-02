#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "MapHandler.h"

typedef struct {
	Vector2 pos;
	Vector2 acceleration;
	Vector2 prevPos;
	Rectangle rect;
} Player;

void CheckPlayerCollisions(Player* player, MapHandler mapHandler) {
	for(int i = 0; i < mapHandler.objectCount; i++) {
		printf("%f, %f - %f, %f\n", player->pos.x, player->pos.y, mapHandler.objects[i].rect.height, mapHandler.objects[i].rect.width);
		if(CheckCollisionRecs(player->rect, mapHandler.objects[i].rect)) {
			printf("Colision");
			player->pos = player->prevPos;
		}
	}
}

void UpdatePlayer(Player* player, MapHandler mapHandler) {
	player->prevPos = player->pos;
	player->pos = Vector2Add(player->pos, player->acceleration);
	player->rect.x = player->pos.x;
	player->rect.y = player->pos.y;
	CheckPlayerCollisions(player, mapHandler);
}


