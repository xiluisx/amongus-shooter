#pragma once
#include <raylib.h>
#include "aMapObject.h"

typedef struct {
	MapObject objects[128]; 
	int objectCount;
} MapHandler;

void AddMapObject(MapHandler* mapHandler, MapObject object);
