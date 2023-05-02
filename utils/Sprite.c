#include <raylib.h>

typedef struct {
	Texture2D texture;
	Rectangle mask;
	int stepSize;
	int curStep;
} Sprite;

Sprite CreateSprite(char *path, int stepSize) {
	Sprite newSprite;
	newSprite.texture = LoadTexture(path);
	newSprite.stepSize = stepSize;
	Rectangle mask = {0, 0, stepSize, newSprite.texture.height};
	newSprite.mask = mask;
	return newSprite;
}

void UpdateSprite(Sprite* sprite) {
	sprite->mask.x = sprite->stepSize * sprite->curStep;
}
