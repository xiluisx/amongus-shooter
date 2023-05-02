#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <math.h>
#include "jimmy.h"
#include "utils/CollisionsHandler.h"
#include "utils/Player.h"

int main() {
    const int screenSize = 512;
	const int screenX = 1024;
	const int screenY = 720;
    InitWindow(screenX, screenY, "Amogus Shooter");
    SetTargetFPS(30);
    TraceLog(foo,"HOLA MUNDO, Esto es un error");

    bool blink = true;
    Texture mogus = LoadTexture("sus2.png");
    Texture map = LoadTexture("assets/map.png");
    Texture gun = LoadTexture("assets/img/player/Gun.png");
	Texture pared = LoadTexture("assets/img/Pared.png");
    Vector2 moguspos = {256,256};
	Player player = {
		.pos = {256, 256},
		.acceleration = {0, 0}
	};
    Vector2 mappos = {0,0};
    Vector2 mousepos;
    Rectangle gunrect = {8,8,8,8};
    Rectangle playerhitbox = {16,16,16,16};
    Camera2D camera = { {screenX/2,screenY/2}, { screenX/2.0f, screenY/2.0f }, 0.0f, 7.0f };

    while (!WindowShouldClose())
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        blink = !blink;
        int mogusDs = 2;
        int mogusNs = 3;

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

		Vector2 prevPos = player.pos;
		player.pos = Vector2Add(player.pos, player.acceleration);

		Rectangle amogusRect = {
			.height = 16,
			.width = 16,
			.x = player.pos.x,
			.y = player.pos.y
		};
		Rectangle paredRect = {
			.height = 16,
			.width = 80,
			.x = 255,
			.y = 240
		};
		if(CheckCollisionRecs(amogusRect, paredRect)){
			player.pos = prevPos;
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



        BeginDrawing();
        ClearBackground(WHITE);
        camera.target = (Vector2){ player.pos.x + 16 / 2, player.pos.y + playerhitbox.height / 2 };
        BeginMode2D(camera);
        

        DrawTextureEx(gun, gunPos, 0, 1, WHITE);
        DrawRectangle(16, 16, 16, 16, blink ? RED:BLUE);
        DrawCollisionsGrid();
        DrawTextureRec(mogus,playerhitbox,player.pos,WHITE);
		DrawTexture(pared, 255, 240, WHITE);
        DrawTextureV(map,mappos,WHITE);
        EndMode2D();
        DrawFPS(10,10);
        EndDrawing();
    }
}
