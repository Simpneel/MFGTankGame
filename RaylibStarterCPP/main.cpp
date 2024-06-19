#pragma warning( push , 0)
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include "SpriteObject.h"
#include "Tank.h"
#include "Turret.h"
#include "Bullet.h"
#include <charconv>

#pragma warning(pop)

int main(int argc, char* argv[])
{

    int screenWidth = 800;
    int screenHeight = 450;
    

    InitWindow(screenWidth, screenHeight, "Tank Game");

    SetTargetFPS(60);

    Image turretImage = LoadImage("ref/tankDark_barrel3.png"); ImageRotateCW(&turretImage);
    Image tankImage = LoadImage("ref/tankBody_huge.png"); ImageRotateCW(&tankImage);
    Image bulletImage = LoadImage("ref/bulletRed1.png"); ImageRotateCW(&bulletImage);

    Texture2D tankTexture = LoadTextureFromImage(tankImage);
    Texture2D turretTexture = LoadTextureFromImage(turretImage);
    Texture2D bulletTexture = LoadTextureFromImage(bulletImage);

    //Texture2D borderTexture = LoadTexture("ref/tileGrass1.png");

    Tank2 enemy; Turret turret2; Bullet bullet2;
    Image enemyImage = LoadImage("ref/tankBody_red.png"); ImageRotateCW(&enemyImage);
    Texture enemySprite = LoadTextureFromImage(enemyImage);
    enemy.Sprite = &enemySprite;
    turret2.Sprite = &turretTexture; bullet2.Sprite = &bulletTexture;

    //SpriteObject Player;
    Tank player;
    Turret turret;

    turret.SetParent(&player);
    turret2.SetParent(&enemy);

    player.Sprite = &tankTexture;
    turret.Sprite = &turretTexture;

    player.SetLocalPosition(250, 225);

    Rectangle topBorder = { 0.0f, screenWidth, screenWidth, 20.0f};
    Rectangle leftBorder = { -20.0f, 0.0f, 20.0f, screenHeight};
    Rectangle botBorder = { screenHeight, screenWidth, screenWidth, 20.0f};
    Rectangle rightBorder = { 20.0f, 20.0f, 20.0f, screenHeight};

    Rectangle collisionCheckBox = { screenWidth / 7, screenHeight / 5, 50.0f, 50.0f };

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        player.Update(deltaTime); enemy.Update(deltaTime);
        turret.Update(deltaTime); turret2.Update(deltaTime);

        

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleLinesEx(collisionCheckBox, 5, DARKPURPLE);

        
        player.Draw();
        enemy.Draw();
        turret.Draw();
        turret2.Draw();
      
        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}