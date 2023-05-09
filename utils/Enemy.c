#include <raylib.h>
#include <raymath.h>
#include "Sprite.h"

typedef struct {
	Vector2 pos;
	Rectangle rect;
	Sprite sprite;
	int isAlive;
	int animationCount;
} Enemy;
