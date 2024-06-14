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

    Image turretImage = LoadImage("ref/tankDark_barrel3.png");
    Image tankImage = LoadImage("ref/tankBody_huge.png");
    Image bulletImage = LoadImage("ref/bulletRed1.png");

    Image tank2Image = LoadImage("ref/tankBody_red.png");
    ImageRotateCW(&tank2Image);
    Texture2D tank2Texture = LoadTextureFromImage(tank2Image);
    ImageRotateCW(&tankImage); ImageRotateCW(&turretImage); ImageRotateCW(&bulletImage);

    Texture2D tankTexture = LoadTextureFromImage(tankImage);
    Texture2D turretTexture = LoadTextureFromImage(turretImage);
    Texture2D bulletTexture = LoadTextureFromImage(bulletImage);

    //SpriteObject Player;
    Tank player;
    Turret turret;
    Bullet bullet;

    Tank2 player2;
    Turret turret2;
    Bullet bullet2;

    turret.SetParent(&player);
    turret2.SetParent(&player2);

    player.Sprite = &tankTexture;
    turret.Sprite = &turretTexture;
    bullet.Sprite = &bulletTexture;

    player2.Sprite = &tank2Texture;
    turret2.Sprite = &turretTexture;
    bullet2.Sprite = &bulletTexture;
    
    player.SetLocalPosition(250, 225);
    player2.SetLocalPosition(750, 225);
    bool drawBullet = false;
    bool drawBullet2 = false;

    int player1Score = 0;
    int player2Score = 0;
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
        float deltaTime = GetFrameTime();
        player.Update(deltaTime);
        turret.Update(deltaTime);
        bullet.Update(deltaTime);
        
        player2.Update(deltaTime); turret2.Update(deltaTime); bullet2.Update(deltaTime);

        if (IsKeyDown(KEY_SPACE)) {
            bullet.SetLocalPosition(turret.GetWorldPosition());
            bullet.SetLocalRotation(turret.GetWorldRotation());
            drawBullet = true;
        }
        if (bullet.GetWorldPosition().x < 0 || bullet.GetWorldPosition().x > screenWidth  || bullet.GetWorldPosition().y < 0 || bullet.GetWorldPosition().y > screenHeight) {
            bullet.SetLocalPosition(turret.GetWorldPosition());
            bullet.SetLocalRotation(turret.GetWorldRotation());
            drawBullet = false;
        }

        if (IsKeyDown(KEY_KP_0)) {
            bullet2.SetLocalPosition(turret2.GetWorldPosition());
            bullet2.SetLocalRotation(turret2.GetWorldRotation());
            drawBullet2 = true;
        }

        if (bullet2.GetWorldPosition().x < 0 || bullet2.GetWorldPosition().x > screenWidth || bullet2.GetWorldPosition().y < 0 || bullet2.GetWorldPosition().y > screenHeight) {
            bullet2.SetLocalPosition(turret2.GetWorldPosition());
            bullet2.SetLocalRotation(turret2.GetWorldRotation());
            drawBullet2 = false;
        }

        std::string p1score = std::to_string(player1Score);
        std::string p2score = std::to_string(player2Score);

        if (abs(bullet2.GetLocalPosition().x - player.GetLocalPosition().x) < 5.0f && abs(bullet2.GetLocalPosition().y - player.GetLocalPosition().y) < 5.0f) {
            player2Score++;
        }
        if (abs(bullet.GetLocalPosition().x - player2.GetLocalPosition().x) < 5.0f && abs(bullet.GetLocalPosition().y - player2.GetLocalPosition().y) < 5.0f) {
            player1Score++;
        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        DrawText(p1score.std::string::c_str(), 15, 15, 4, DARKPURPLE);
        DrawText(p2score.std::string::c_str(), 725, 15, 4, RED);

        player.Draw();
        turret.Draw();
        
        player2.Draw();
        turret2.Draw();
        if (drawBullet) bullet.Draw();
        if (drawBullet2) bullet2.Draw();

        EndDrawing();
        
        //----------------------------------------------------------------------------------
    }

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}