#include "Enemy.h"
#include "Player.h"

typedef struct {
	int curRound;
	Enemy enemies[50];
	int enemiesCount;
	Player* player;
} GameHandler;

void HandleNewRound(GameHandler* game);

void CheckEnemies(GameHandler* game);

void UpdateEnemy(Enemy* enemy, GameHandler* game);

void DrawEnemies(GameHandler* game);
