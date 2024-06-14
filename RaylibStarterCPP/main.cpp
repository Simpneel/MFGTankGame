#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include "SpriteObject.h"
#include "Tank.h"

#pragma warning(pop)

int main(int argc, char* argv[])
{
    
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tank Game");

    SetTargetFPS(60);

    Texture2D tankTexture = LoadTexture("ref/tankBody_huge.png");
    Texture2D turretTexture = LoadTexture("ref/tankDark_barrel3.png");

    //SpriteObject Player;
    Tank player;
    player.Sprite = &tankTexture;
    player.SetLocalPosition(screenWidth / 2, screenHeight / 2);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        player.Update(deltaTime);

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        player.Draw();
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}