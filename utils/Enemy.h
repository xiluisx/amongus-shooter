#include <raylib.h>
#include <raymath.h>
#include "MapHandler.h"

typedef struct {
	Vector2 pos;
	Rectangle rect;
	Sprite sprite;
	int isAlive;
	int animationCount;
} Enemy;

