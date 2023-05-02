#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <math.h>
#include "jimmy.h"
#include "utils/CollisionsHandler.h"
#include "utils/Player.h"
#include "utils/MapHandler.h"

int main() {
	const int screenX = 1024;
	const int screenY = 720;
    InitWindow(screenX, screenY, "Amogus Shooter");
    SetTargetFPS(30);
    TraceLog(foo,"HOLA MUNDO, Esto es un error");

    bool blink = true;
	MapHandler mapHandler;
    Texture mogus = LoadTexture("sus2.png");
    Texture map = LoadTexture("assets/map.png");
    Texture gun = LoadTexture("assets/img/player/Gun.png");
	MapObject paredObj = {
		.texture = LoadTexture("assets/img/Pared.png"),
		.rect = {255, 240, 80, 16}
	};
	AddMapObject(&mapHandler, paredObj);

	Player player = {
		.pos = {256, 256},
		.acceleration = {0, 0},
		.rect = {256, 256, 16, 16}
	};
    Vector2 mappos = {0,0};
    Rectangle gunrect = {8,8,8,8};
    Rectangle playerhitbox = {16,16,16,16};
    Camera2D camera = { {screenX/2.0,screenY/2.0}, { screenX/2.0f, screenY/2.0f }, 0.0f, 7.0f };

    while (!WindowShouldClose())
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        blink = !blink;

        if (mouseWorldPos.x<player.pos.x+8){
            playerhitbox.width = -16;
            gunrect.width = -16;
            }
        if (mouseWorldPos.x>player.pos.x+8){
            playerhitbox.width = 16;
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

		Rectangle paredRect = {
			.height = 16,
			.width = 80,
			.x = 255,
			.y = 240
		};
	
		/*
		if(CheckCollisionRecs(player.rect, paredObj.rect)){
			player.pos = player.prevPos;
		}*/
		
		
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



        BeginDrawing();
        ClearBackground(WHITE);
        camera.target = (Vector2){ player.pos.x + 16 / 2, player.pos.y + playerhitbox.height / 2 };
        BeginMode2D(camera);
        

        DrawTextureEx(gun, gunPos, 0, 1, WHITE);
        DrawRectangle(16, 16, 16, 16, blink ? RED:BLUE);
        DrawCollisionsGrid();
        DrawTextureRec(mogus,playerhitbox,player.pos,WHITE);
		DrawTexture(paredObj.texture, 255, 240, WHITE);
        DrawTextureV(map,mappos,WHITE);
        EndMode2D();
        DrawFPS(10,10);
        EndDrawing();
    }
}
