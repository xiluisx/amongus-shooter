#include <stdio.h>
#include <raylib.h>

void DrawCollisionsGrid()
{
    for (int i = 0; i < 512; i+=16)
    {
        for (int j = 0; j < 512; j+=16)
        {
            DrawRectangleLines(i,j,16,16,GREEN);
        }
    }
}
