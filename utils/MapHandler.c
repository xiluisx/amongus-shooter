#include <raylib.h>
#include <stdio.h>
#include "aMapObject.h"

typedef struct {
	MapObject objects[128]; 	
	int objectCount;
} MapHandler;

void AddMapObject(MapHandler* mapHandler, MapObject object) {
	printf("Adding Object at: %i\n", mapHandler->objectCount);
	mapHandler->objects[mapHandler->objectCount] = object;
	mapHandler->objectCount++;
}

void RenderMapObjects(MapHandler mapHandler) {
	for(int i = 0; i < mapHandler.objectCount; i++) {
		MapObject obj = mapHandler.objects[i];
		Vector2 pos = {obj.rect.x, obj.rect.y};
		DrawTextureRec(obj.sprite.texture, obj.sprite.mask, pos, WHITE);
	}
}
