#include <raylib.h>
#include "MapHandler.h"

typedef struct {
	Vector2 pos;	
	Vector2 acceleration;
	Vector2 prevPos;
	Rectangle rect;
	Sprite sprite;
} Player;

void CheckPlayerCollisions(Player* player, MapHandler mapHandler);

void UpdatePlayer(Player* player, MapHandler mapHandler);
