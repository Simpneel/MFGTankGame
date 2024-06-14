#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include "SpriteObject.h"
#include "Tank.h"
#include "Turret.h"

#pragma warning(pop)

int main(int argc, char* argv[])
{
    
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Tank Game");

    SetTargetFPS(60);

    Image turretImage = LoadImage("ref/tankDark_barrel3.png");
    Image tankImage = LoadImage("ref/tankBody_huge.png");
    ImageRotateCW(&tankImage); ImageRotateCW(&turretImage);
    Texture2D tankTexture = LoadTextureFromImage(tankImage);
    Texture2D turretTexture = LoadTextureFromImage(turretImage);

    //SpriteObject Player;
    Tank player;
    Turret turret;
    
    player.Sprite = &tankTexture;
    turret.Sprite = &turretTexture;
    player.SetLocalPosition(screenWidth / 2, screenHeight / 2);
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        turret.SetLocalPosition(player.GetLocalPosition().x - 7.5f, player.GetLocalPosition().y - 7.5f);
       
        float deltaTime = GetFrameTime();
        player.Update(deltaTime);
        turret.Update(deltaTime);

        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        player.Draw();
        turret.Draw();
        
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}