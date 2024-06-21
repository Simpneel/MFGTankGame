#pragma warning( push , 0)
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include "SpriteObject.h"
#include "Tank.h"
#include "Turret.h"
#include "Bullet.h"
#include <vector>

#include "enet_client.h"
#include "enet_server.h"

//#include "enet_wrapper.h"
#pragma warning(pop)

int main()
{

    int screenWidth = 800;
    int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "Tank Game");

    SetTargetFPS(60);

    Image turretImage = LoadImage("ref/tankDark_barrel3.png"); ImageRotateCW(&turretImage); //Creating images for all required objects and flipping them 90 deg clockwise
    Image tankImage = LoadImage("ref/tankBody_blue.png"); ImageRotateCW(&tankImage);
    Image bulletImage = LoadImage("ref/bulletRed1.png"); ImageRotateCW(&bulletImage);

    Texture2D tankTexture = LoadTextureFromImage(tankImage);    //Creating textures using pre flipped images
    Texture2D turretTexture = LoadTextureFromImage(turretImage);
    Texture2D bulletTexture = LoadTextureFromImage(bulletImage);


    Tank redPlayer; Turret turret2; Bullet bullet2;                                           //Creating an enemy object
    Image enemyImage = LoadImage("ref/tankBody_red.png"); ImageRotateCW(&enemyImage);
    Texture enemySprite = LoadTextureFromImage(enemyImage);
    redPlayer.Sprite = &enemySprite;
    turret2.Sprite = &turretTexture; bullet2.Sprite = &bulletTexture;

    //SpriteObject Player;
    Tank bluePlayer;                                                                          //Creating main player object
    Turret turret;
    std::vector<Bullet> playerMag;
    std::vector<Bullet> enemyMag;

    turret.SetParent(&bluePlayer);                                                            //Setting player turret's parent to be the main player object
    turret2.SetParent(&redPlayer);                                                            //Setting enemy turret's parent to be the enemy player object

    bluePlayer.Sprite = &tankTexture;
    turret.Sprite = &turretTexture;

    bluePlayer.SetLocalPosition(266, 225);
    redPlayer.SetLocalPosition(533, 225);
    redPlayer.SetLocalRotation(redPlayer.GetLocalRotation() + 3.14);

    Rectangle topBorder = { 0.0f, -20.0f, (float)screenWidth, 20.0f };
    Rectangle leftBorder = { -20.0f, 0.0f, 20.0f, (float)screenHeight };
    Rectangle botBorder = { 0.0f, (float)screenHeight, (float)screenWidth, 20.0f };
    Rectangle rightBorder = { (float)screenWidth, 20.0f, 20.0f, (float)screenHeight };
    Rectangle collisionCheckBox = { screenWidth / 7, screenHeight / 5, 50.0f, 50.0f };

    Texture2D barrelRust = LoadTexture("ref/barrelRust_side.png");

    int letterCount = 0;
    char choice[4]{};

    BeginDrawing();
    {
        ClearBackground(DARKGRAY);
        DrawText("Enter 'HOST' to create a game lobby\nEnter 'JOIN' to join another game\nplease type those exactly\n", screenWidth / 2.0f, screenHeight / 2.0f - 50, 3, DARKPURPLE);
        Rectangle textBox = { screenWidth / 2.0f, screenHeight / 2.0f, 75, 40 };
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
            int key = GetKeyPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (letterCount < 5)) {
                    choice[letterCount] = (char)key;
                }
                choice[letterCount + 1] = '\0';
                key = GetKeyPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                choice[letterCount] = '\0';
            }
        }
        else EnableCursor();
    }
    EndDrawing();

    if (choice == "HOST") {
        ENet_Server player1;
        GameState serverState;
        while (!WindowShouldClose())
        {
            player1.ReceivePacket(&serverState);
            redPlayer.SetLocalPosition(serverState.clientPosition);
            float deltaTime = GetFrameTime();
            bluePlayer.Update(deltaTime); 
            turret.Update(deltaTime); 
            redPlayer.Update(deltaTime);
            turret2.Update(deltaTime);

            if (IsKeyPressed(KEY_SPACE)) {
                Bullet newBullet;
                newBullet.Sprite = &bulletTexture;
                newBullet.SetLocalPosition(turret.GetWorldPosition());
                newBullet.SetLocalRotation(turret.GetWorldRotation());
                playerMag.push_back(newBullet);
            }
            else if (IsKeyPressed(KEY_W)) bluePlayer.Direction = KEY_W;
            else if (IsKeyPressed(KEY_A)) bluePlayer.Direction = KEY_A;
            else if (IsKeyPressed(KEY_S)) bluePlayer.Direction = KEY_S;
            else if (IsKeyPressed(KEY_D)) bluePlayer.Direction = KEY_D;
            

            serverState.serverPosition = bluePlayer.GetWorldPosition();
            serverState.clientPosition = redPlayer.GetWorldPosition();
            player1.SendPacket(serverState);


            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(barrelRust, collisionCheckBox, { collisionCheckBox.x,collisionCheckBox.y }, WHITE);
            
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

            bluePlayer.Draw();
            redPlayer.Draw();
            turret.Draw();
            turret2.Draw();

            EndDrawing();

            //----------------------------------------------------------------------------------
        }

        CloseWindow();
    }

    else if (choice == "JOIN") {
        ENet_Client player2;
        GameState clientState;
        while (!WindowShouldClose())
        {
            player2.ReceivePacket(&clientState);

            float deltaTime = GetFrameTime();
            bluePlayer.Update(deltaTime);
            turret.Update(deltaTime);
            redPlayer.Update(deltaTime);
            turret2.Update(deltaTime);

            if (IsKeyPressed(KEY_SPACE)) {
                Bullet newBullet;
                newBullet.Sprite = &bulletTexture;
                newBullet.SetLocalPosition(turret.GetWorldPosition());
                newBullet.SetLocalRotation(turret.GetWorldRotation());
                playerMag.push_back(newBullet);
            }
            else if (IsKeyPressed(KEY_W)) bluePlayer.Direction = KEY_W;
            else if (IsKeyPressed(KEY_A)) bluePlayer.Direction = KEY_A;
            else if (IsKeyPressed(KEY_S)) bluePlayer.Direction = KEY_S;
            else if (IsKeyPressed(KEY_D)) bluePlayer.Direction = KEY_D;
            
            player2.SendPacket(clientState);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTextureRec(barrelRust, collisionCheckBox, { collisionCheckBox.x,collisionCheckBox.y }, WHITE);

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

            bluePlayer.Draw();
            redPlayer.Draw();
            turret.Draw();
            turret2.Draw();

            EndDrawing();

            //----------------------------------------------------------------------------------
        }
    return 0;
}
