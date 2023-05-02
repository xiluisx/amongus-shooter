#include <raylib.h>

typedef struct {
	Texture2D texture;
	Rectangle mask;
	int stepSize;
	int curStep;
} Sprite;

Sprite CreateSprite(char *path, int stepSize);

void UpdateSprite(Sprite* sprite);
