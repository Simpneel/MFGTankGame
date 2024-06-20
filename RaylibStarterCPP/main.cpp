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
#include <vector>

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
    std::vector<Bullet> playerMag;
    std::vector<Bullet> enemyMag;

    turret.SetParent(&player);
    turret2.SetParent(&enemy);

    player.Sprite = &tankTexture;
    turret.Sprite = &turretTexture;

    player.SetLocalPosition(250, 225);
    enemy.SetLocalPosition(750, 225);
    enemy.SetLocalRotation(enemy.GetLocalRotation() + 3.14);

    Rectangle topBorder = { 0.0f, -20.0f, screenWidth, 20.0f};
    Rectangle leftBorder = { -20.0f, 0.0f, 20.0f, screenHeight};
    Rectangle botBorder = { 0.0f, screenHeight, screenWidth, 20.0f};
    Rectangle rightBorder = { screenWidth, 20.0f, 20.0f, screenHeight};
    Rectangle collisionCheckBox = { screenWidth / 7, screenHeight / 5, 50.0f, 50.0f };

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        player.Update(deltaTime); enemy.Update(deltaTime);
        turret.Update(deltaTime); turret2.Update(deltaTime);

        if (IsKeyDown(KEY_F)) {
            screenWidth = 1366;
            screenHeight = 768;
            SetWindowSize(screenWidth, screenHeight);
        }
        if (IsKeyUp(KEY_F)) {
            screenWidth = 800;
            screenHeight = 450;
            SetWindowSize(screenWidth, screenHeight);
        }
        if (IsKeyPressed(KEY_SPACE)) {
            Bullet newBullet;
            newBullet.Sprite = &bulletTexture;
            newBullet.SetLocalPosition(turret.GetWorldPosition());
            newBullet.SetLocalRotation(turret.GetWorldRotation());
            playerMag.push_back(newBullet);
        }
        if (IsKeyPressed(KEY_KP_0)) {
            Bullet newBullet;
            newBullet.Sprite = &bulletTexture;
            newBullet.SetLocalPosition(turret2.GetWorldPosition());
            newBullet.SetLocalRotation(turret2.GetWorldRotation());
            enemyMag.push_back(newBullet);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleLinesEx(collisionCheckBox, 5, DARKPURPLE);

        /*DrawRectangleLinesEx(botBorder, 5, DARKGRAY);
        DrawRectangleLinesEx(rightBorder, 5, DARKGRAY);
        DrawRectangleLinesEx(leftBorder, 5, DARKGRAY);
        DrawRectangleLinesEx(topBorder, 5, DARKGRAY);*/


        for (int x = 0; x < playerMag.size(); x++) {
            playerMag.at(x).Update(deltaTime);
            playerMag.at(x).Draw();
            if (playerMag.at(x).CheckCollision(collisionCheckBox) || playerMag.at(x).CheckCollision(topBorder, botBorder, leftBorder, rightBorder)) {
                playerMag.erase(playerMag.cbegin());
                break;
            }
            if (x == playerMag.size()) {
                playerMag.clear();
                break;
            }
        }

        for (int x = 0; x < enemyMag.size(); x++) {
            enemyMag.at(x).Update(deltaTime);
            enemyMag.at(x).Draw();
            if (enemyMag.at(x).CheckCollision(collisionCheckBox) || enemyMag.at(x).CheckCollision(topBorder, botBorder, leftBorder, rightBorder)) {
                enemyMag.erase(enemyMag.cbegin());
                break;
            }
            if (x == enemyMag.size()) {
                enemyMag.clear();
                break;
            }
        }
        
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