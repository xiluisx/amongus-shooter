#include <raylib.h>

int main(int argc, char const *argv[])
{
    InitWindow(600, 600, "Amongus Shooter");
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
    return 0;
}
