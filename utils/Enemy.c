#include <raylib.h>
#include <raymath.h>
#include "Sprite.h"

typedef struct {
	Vector2 pos;
	Vector2 prevPos;
	Rectangle rect;
	Sprite sprite;
	int isAlive;
	int animationCount;
} Enemy;
