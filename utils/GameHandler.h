#include "Enemy.h"
#include "MapHandler.h"
#include "Player.h"
#include "SpawnLocation.h"

typedef struct {
	int curRound;
	Enemy enemies[50];
	int enemiesCount;
	Player* player;
	MapHandler* mapHandler;
	SpawnLocation spawns[4];
} GameHandler;

void HandleNewRound(GameHandler* game, SpawnLocation spawns[4]);

void CheckEnemies(GameHandler* game, SpawnLocation spawns[4]);

void UpdateEnemy(Enemy* enemy, GameHandler* game, MapHandler* mapHandler);

void DrawEnemies(GameHandler* game);
