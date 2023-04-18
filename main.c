#include <raylib.h>
#include "jimmy.h"
#include "utils/CollisionsHandler.h"

int main() {
    const int screenSize = 512;
    InitWindow(screenSize, screenSize, "JimmyGame");
    SetTargetFPS(30);
    TraceLog(foo,"HOLA MUNDO, Esto es un error");

    bool blink = true;
    Texture mogus = LoadTexture("sus2.png");
    Texture map = LoadTexture("assets/map.png");
    Vector2 moguspos = {256,256};
    Vector2 mappos = {0,0};
    Vector2 mousepos;
    Rectangle playerhitbox = {16,16,16,16};
    Camera2D camera = {moguspos, { screenSize/2.0f, screenSize/2.0f }, 0.0f, 7.0f };

    while (!WindowShouldClose())
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

        blink = !blink;
        int mogusDs = 2;
        int mogusNs = 3;

        if (mouseWorldPos.x<moguspos.x+8){
            playerhitbox.width = -16;
            }
        if (mouseWorldPos.x>moguspos.x+8){
            playerhitbox.width = 16;
            }

        if(moguspos.x<=map.width&&moguspos.y<=map.height){
            if(IsKeyDown(KEY_W)&&IsKeyDown(KEY_D)){
            moguspos.y -= mogusDs;
            moguspos.x += mogusDs;
            mousepos.x += mogusDs;
            }
            else if(IsKeyDown(KEY_S)&&IsKeyDown(KEY_D)){
                moguspos.y += mogusDs;
                moguspos.x += mogusDs;
                mousepos.x += mogusDs;
            }
            else if(IsKeyDown(KEY_W)&&IsKeyDown(KEY_A)){
                moguspos.y -= mogusDs;
                moguspos.x -= mogusDs;
                mousepos.x -= mogusDs;
            }
            else if(IsKeyDown(KEY_S)&&IsKeyDown(KEY_A)){
                moguspos.y += mogusDs;
                moguspos.x -= mogusDs;
                mousepos.x -= mogusDs;
            }
            else if(IsKeyDown(KEY_A)){
                moguspos.x -= mogusNs;
                mousepos.x -= mogusDs;
            }
            else if(IsKeyDown(KEY_W)){
                moguspos.y -= mogusNs;
            }
            else if(IsKeyDown(KEY_S)){
                moguspos.y += mogusNs;
            }
            else if(IsKeyDown(KEY_D)){
                moguspos.x += mogusNs;
                mousepos.x += mogusDs;
            }
        }

        BeginDrawing();
            ClearBackground(WHITE);
        camera.target = (Vector2){ moguspos.x + 16 / 2, moguspos.y + playerhitbox.height / 2 };
        BeginMode2D(camera);
        DrawRectangle(16, 16, 16, 16, blink ? RED:BLUE);
        DrawFPS(10,10);
        DrawCollisionsGrid();
        DrawTextureRec(mogus,playerhitbox,moguspos,WHITE);
        DrawTextureV(map,mappos,WHITE);
        EndMode2D();
        EndDrawing();
    }
}