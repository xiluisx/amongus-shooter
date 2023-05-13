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

	MapObject paredObj = {
		.texture = LoadTexture("assets/img/Pared.png"),
		.rect = {255, 240, 80, 16}
	};
	AddMapObject(&mapHandler, paredObj);
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
	Player player = {
		.pos = {256, 256},
		.acceleration = {0, 0},
		.rect = {256, 256, 16, 16},
		.sprite = CreateSprite("assets/img/player/sussprites.png", 16)
	};
    Vector2 vorderecho = {496, 16};
    Vector2 vordinf = {0, 496};

	Sprite bullet = CreateSprite("assets/img/Bullet.png", 8);

	GameHandler game = {
		.curRound = 1,
		.enemiesCount = 0,
		.player	= &player
	};

	HandleNewRound(&game);

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

    while (!WindowShouldClose())
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        switch(currentScreen){
            case LOGO:{
                framesCounter++;
                if (framesCounter > 120){
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:{
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                    currentScreen = GAMEPLAY;

                }
            } break;
            case GAMEPLAY:{
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)){
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:{
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)){
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
			UpdateEnemy(&game.enemies[i], &game);
		}

		Vector2 origin = {
            .x = 8,
            .y = 8
        };
        double angleToMouse = Vector2Angle(Vector2Add(player.pos, origin), mouseWorldPos);
		Vector2 shootingPos = {cos(angleToMouse), sin(angleToMouse)};

        float xPos = 20 * cos(angleToMouse);
        float yPos = 20 * sin(angleToMouse);
        Vector2 gunPos = {
            .x = player.pos.x + xPos + 4,
            .y = player.pos.y + yPos + 4
        };


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
            case GAMEPLAY:{
                camera.target = (Vector2){ player.pos.x + 16.0 / 2, player.pos.y + playerhitbox.height / 2 };
                BeginMode2D(camera);
                DrawTextureEx(gun, gunPos, 0, 1, WHITE);
                DrawCollisionsGrid();
                DrawTextureRec(player.sprite.texture,player.sprite.mask,player.pos,WHITE);
                DrawEnemies(&game);
                DrawTexture(paredObj.texture, 255, 240, WHITE);

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

                DrawRectangle(0, 0, screenX, screenY, BLUE);
                DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

            } break;
            default: break;
        }


        EndDrawing();
    }
}
