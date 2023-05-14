#include "Enemy.h"
#include "MapHandler.h"
#include "Player.h"

typedef struct {
	int curRound;
	Enemy enemies[50];
	int enemiesCount;
	Player* player;
	MapHandler* mapHandler;
} GameHandler;

void HandleNewRound(GameHandler* game);

void CheckEnemies(GameHandler* game);

void UpdateEnemy(Enemy* enemy, GameHandler* game, MapHandler* mapHandler);

void DrawEnemies(GameHandler* game);
