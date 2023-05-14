#include <raylib.h>
#include "MapHandler.h"
#include "Bullet.h"

typedef struct {
	Vector2 pos;
	Vector2 acceleration;
	Vector2 prevPos;
	Rectangle rect;
	int animationCount;
	Sprite sprite; 
	int bulletCount;
	Bullet bullets[50];
	int reloadCount;
} Player;

void UpdateBullets(Sprite sprite, Player* player);

void AddBullet(Player* player, Vector2 dir);

void CheckPlayerCollisions(Player* player, MapHandler mapHandler);

void UpdatePlayer(Player* player, MapHandler mapHandler);
