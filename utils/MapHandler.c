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
