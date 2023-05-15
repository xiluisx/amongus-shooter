#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <math.h>
#include "utils/CollisionsHandler.h"
#include "utils/MapHandler.h"
#include "utils/GameHandler.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main() {

	const int screenX = 800;
	const int screenY = 600;
    InitWindow(screenX, screenY, "Amogus Shooter");
    SetTargetFPS(30);

	MapHandler mapHandler = {0};
	
    Texture map = LoadTexture("assets/map.png");
    Texture gun = LoadTexture("assets/img/player/Gun.png");

    MapObject Bordesup = {
            .texture = LoadTexture("assets/img/bordesup.png"),
            .rect = {0, 0, 512, 16}
    };
    AddMapObject(&mapHandler, Bordesup);
    MapObject Bordeizq = {
            .texture = LoadTexture("assets/img/bordeizq.png"),
            .rect = {0, 16, 16, 480}
    };
    AddMapObject(&mapHandler, Bordeizq);
    MapObject Bordeinf = {
            .texture = LoadTexture("assets/img/bordesup.png"),
            .rect = {0, 496, 512, 16}
    };
    AddMapObject(&mapHandler, Bordeinf);
    MapObject Borderecho = {
            .texture = LoadTexture("assets/img/bordeizq.png"),
            .rect = {496, 16, 16, 480}
    };
    AddMapObject(&mapHandler, Borderecho);
    Vector2 vorderecho = {496, 16};
    Vector2 vordinf = {0, 496};
    Texture muroacero = LoadTexture("assets/img/murometal.png");
    MapObject muro1 = {
            .texture = muroacero,
            .rect = {96, 64, 320, 16}
    };
    AddMapObject(&mapHandler, muro1);
    MapObject muro2 = {
            .texture = muroacero,
            .rect = {96, 80, 16, 32}
    };
    AddMapObject(&mapHandler, muro2);
    MapObject muro3 = {
            .texture = muroacero,
            .rect = {400, 80, 16, 32}
    };
    AddMapObject(&mapHandler, muro3);
    MapObject muro4 = {
            .texture = muroacero,
            .rect = {96, 144, 16, 80}
    };
    AddMapObject(&mapHandler, muro4);
    MapObject muro5 = {
            .texture = muroacero,
            .rect = {112, 208, 112, 16}
    };
    AddMapObject(&mapHandler, muro5);
    MapObject muro6 = {
            .texture = muroacero,
            .rect = {288, 208, 112, 16}
    };
    AddMapObject(&mapHandler, muro6);
    MapObject muro7 = {
            .texture = muroacero,
            .rect = {400, 144, 16, 80}
    };
    AddMapObject(&mapHandler, muro7);
    MapObject muro8 = {
            .texture = muroacero,
            .rect = {160, 208, 16, 80}
    };
    AddMapObject(&mapHandler, muro8);
    MapObject muro9 = {
            .texture = muroacero,
            .rect = {336, 208, 16, 80}
    };
    AddMapObject(&mapHandler, muro9);
    MapObject muro10 = {
            .texture = muroacero,
            .rect = {160, 320, 16, 80}
    };
    AddMapObject(&mapHandler, muro10);
    MapObject muro11 = {
            .texture = muroacero,
            .rect = {176, 384, 64, 16}
    };
    AddMapObject(&mapHandler, muro11);
    MapObject muro12 = {
            .texture = muroacero,
            .rect = {272, 384, 64, 16}
    };
    AddMapObject(&mapHandler, muro12);
    MapObject muro13 = {
            .texture = muroacero,
            .rect = {336, 320, 16, 80}
    };
    AddMapObject(&mapHandler, muro13);
    MapObject muro14 = {
            .texture = muroacero,
            .rect = {16, 160, 80, 16}
    };
    AddMapObject(&mapHandler, muro14);
    MapObject muro15 = {
            .texture = muroacero,
            .rect = {416, 160, 80, 16}
    };
    AddMapObject(&mapHandler, muro15);
    MapObject muro16 = {
            .texture = muroacero,
            .rect = {16, 336, 144, 16}
    };
    AddMapObject(&mapHandler, muro16);
    MapObject muro17 = {
            .texture = muroacero,
            .rect = {352, 336, 144, 16}
    };
    AddMapObject(&mapHandler, muro17);

	Player player = {
		.pos = {256, 256},
		.acceleration = {0, 0},
		.rect = {256, 256, 16, 16},
		.sprite = CreateSprite("assets/img/player/sussprites.png", 16),
		.reloadCount = 0
	};

	Sprite bullet = CreateSprite("assets/img/Bullet.png", 8);

	SpawnLocation s1 = {{118,300}};
	SpawnLocation s2 = {{248,104}};
	SpawnLocation s3 = {{248,383}};
	SpawnLocation s4 = {{414,293}};

	SpawnLocation spawns[4] = {s1,s2,s3,s4};
	printf("s1 = %f, %f\n", s1.pos.x, s1.pos.y);
	GameHandler game = {
		.curRound = 1,
		.enemiesCount = 0,
		.player	= &player,
		.mapHandler = &mapHandler,
		.spawns = {s1, s2, s3, s4}
	};

	printf("s1game = %f, %f\n", game.spawns[0].pos.x, game.spawns[0].pos.y);

	HandleNewRound(&game, spawns);

    Vector2 mappos = {0,0};
    Rectangle gunrect = {8,8,8,8};
    Rectangle playerhitbox = {16,16,16,16};
    Camera2D camera = { {screenX/2.0,screenY/2.0}, { screenX/2.0f, screenY/2.0f }, 0.0f, 7.0f };

    GameScreen currentScreen = LOGO;
    InitAudioDevice();
    Music pvzsong = LoadMusicStream("assets/sound/pvz-amongus.mp3");
    int framesCounter = 0;
    Rectangle bgrec = {80,45,80,45};
    Rectangle menungusrec = {80,45,80,45};
    Texture menungus = LoadTexture("assets/img/menungus.png");
    Texture menubg = LoadTexture("assets/img/menubg.png");
    Camera2D camera2 = {{0,0},{0,0}, 0.0f, 10.7f };
    Texture deathscreen = LoadTexture("assets/img/deathscreen.png");
    int Vida = 3;

    while (!WindowShouldClose())
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        switch(currentScreen){
            case LOGO:{
                framesCounter++;
                if (framesCounter > 0){
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:{
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    currentScreen = GAMEPLAY;

                }
            } break;
            case GAMEPLAY:{
                if (IsKeyPressed(KEY_ENTER)||Vida < 1){
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:{
                if (IsKeyPressed(KEY_ENTER)){
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }

        if (mouseWorldPos.x<player.pos.x+8){
            player.sprite.mask.width = -16;
            gunrect.width = -16;
            }
        if (mouseWorldPos.x>player.pos.x+8){
            player.sprite.mask.width = 16;
            gunrect.width = 16;
        }

		player.acceleration.x = 0;
		player.acceleration.y = 0;

        if(player.pos.x<=map.width&&player.pos.y<=map.height){
            if(IsKeyDown(KEY_W)) {
				player.acceleration.y = -2;
            }
			if(IsKeyDown(KEY_D)) {
				player.acceleration.x = 2;
			}
			if(IsKeyDown(KEY_S)) {
				player.acceleration.y = 2;
			}
			if(IsKeyDown(KEY_A)) {
				player.acceleration.x = -2;
			}
        }

		if(player.acceleration.x != 0 && player.acceleration.y != 0) {
			player.acceleration.x /= 1.5;
			player.acceleration.y /= 1.5;
		}

		UpdatePlayer(&player, mapHandler);
		for(int i = 0; i < game.enemiesCount; i++) {
			UpdateEnemy(&game.enemies[i], &game, &mapHandler);
		}

		Vector2 origin = {
            .x = 8,
            .y = 8
        };
        double angleToMouse = Vector2Angle(Vector2Add(player.pos, origin), mouseWorldPos);

        float xPos = 20 * cos(angleToMouse);
        float yPos = 20 * sin(angleToMouse);
        Vector2 gunPos = {
            .x = player.pos.x + xPos + 4,
            .y = player.pos.y + yPos + 4
        };

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 shootingPos = {cos(angleToMouse), sin(angleToMouse)};
			AddBullet(&player, shootingPos);
        }
		if(IsKeyDown(KEY_I)) {
			printf("%f, %f\n", player.pos.x, player.pos.y);
            printf("%d,\n", Vida);
		}

		CheckEnemies(&game, spawns);

        for(int i=0;i<50;i++){
            int collision = CheckCollisionRecs(player.rect, game.enemies[i].rect );
            if(collision){
                Vida -= 1;
                game.enemies[i].pos.x = 512;
                game.enemies[i].isAlive = false;
                break;
            }
        }


        BeginDrawing();
        ClearBackground(WHITE);

        switch(currentScreen){
            case LOGO:{
                DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
            } break;
            case TITLE:{
                BeginMode2D(camera2);
                UpdateMusicStream(pvzsong);
                PlayMusicStream(pvzsong);
                DrawTextureRec(menubg,bgrec,mappos,WHITE);
                DrawTextureRec(menungus,menungusrec,mappos,WHITE);
                bgrec.x -=0.5;
                if (bgrec.x ==-80){
                    bgrec.x = 0;
                }

                EndMode2D();

            } break;
            case GAMEPLAY: {
                camera.target = (Vector2) {player.pos.x + 16.0 / 2, player.pos.y + playerhitbox.height / 2};
                BeginMode2D(camera);
                DrawTextureEx(gun, gunPos, 0, 1, WHITE);
                DrawCollisionsGrid();
                DrawTextureRec(player.sprite.texture, player.sprite.mask, player.pos, WHITE);
				UpdateBullets(bullet, &player);
                DrawEnemies(&game);

                DrawTextureV(map,mappos,WHITE);
                DrawTexture(Bordesup.texture, 0, 0, WHITE);
                DrawTexture(Bordeizq.texture, 0, 16, WHITE);
                DrawTextureRec(Bordeinf.texture,Bordeinf.rect, vordinf, WHITE);
                DrawTextureRec(Borderecho.texture,Borderecho.rect, vorderecho, WHITE);
                Bordeinf.rect.height = -16;


                EndMode2D();
                DrawFPS(10,10);

            } break;
            case ENDING:{
                BeginMode2D(camera2);
                DrawRectangle(0,0,100,100,BLACK);
                DrawTexture(deathscreen,0,0,WHITE);
                EndMode2D();

            } break;
            default: break;
        }


        EndDrawing();
    }
}
