#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
const int screenWidth = 500;
const int screenHeight = 680;
int framesCounter = 0;

int main()
{
    InitWindow(screenWidth, screenHeight, "C++CJia Tetris!");
    
    GameScreen currentScreen = LOGO;
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Image background = LoadImage("resources/background.png"); // initialize background
    ImageResize(&background, 500, 680);
    Texture2D texture = LoadTextureFromImage(background);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                UpdateMusicStream(game.music);
                game.HandleInput();
                if (EventTriggered(0.2))
                {
                    game.MoveBlockDown();
                }
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = TITLE;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

                } break;
                case TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                } break;
                case GAMEPLAY:
                {
                    ClearBackground(darkBlue);
                    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
                    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
                    if (game.gameOver)
                    {
                        DrawTextEx(font, "GAME OVER!", {320, 450}, 38, 2, WHITE);
                        currentScreen = ENDING;
                    }
                    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

                    char scoreText[10];
                    sprintf(scoreText, "%d", game.score);
                    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

                    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
                    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
                    DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
                    game.Draw();

                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                } break;
                default: break;
            }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!
    UnloadTexture(texture);

    CloseWindow();        // Close window and OpenGL context


    return 0;
}