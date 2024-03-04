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
    Image grid = LoadImage("resources/grid.PNG"); // initialize components
    Image gameover = LoadImage("resources/IMG_5410.PNG"); // initialize background
    Image finalscore = LoadImage("resources/IMG_5421.PNG"); // initialize components
    Image logo = LoadImage("resources/IMG_5424.PNG"); // initialize components
    Image enter = LoadImage("resources/IMG_5423.PNG"); // initialize components
    ImageResize(&background, 500, 680);
    ImageResize(&grid, 500, 680);
    ImageResize(&gameover, 500, 150);
    ImageResize(&finalscore, 500, 100);
    ImageResize(&logo, 500, 680);
    ImageResize(&enter, 500, 150);
    Texture2D texture = LoadTextureFromImage(background);
    Texture2D frame = LoadTextureFromImage(grid);
    Texture2D endgame = LoadTextureFromImage(gameover);
    Texture2D finalpoints = LoadTextureFromImage(finalscore);
    Texture2D pic = LoadTextureFromImage(logo);
    Texture2D startgame = LoadTextureFromImage(enter);

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
                if (IsKeyPressed(KEY_ENTER))
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
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = TITLE;
                    UpdateMusicStream(game.music);
                    game.HandleInput();
                    if (EventTriggered(0.2))
                    {
                        game.MoveBlockDown();
                    }
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
                    DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
                    DrawText("LOADING.. C++CJIA", 20, 20, 40, WHITE);

                } break;
                case TITLE:
                {
                    DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
                    DrawTexture(pic, screenWidth - pic.width, screenHeight - pic.height, WHITE);
                    DrawTexture(startgame, screenWidth - startgame.width, screenHeight - startgame.height, WHITE);

                } break;
                case GAMEPLAY:
                {
                    ClearBackground(darkBlue);
                    DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
                    DrawTexture(frame, screenWidth - grid.width, screenHeight - grid.height, WHITE);
                    
                    if (game.gameOver)
                    {
                        currentScreen = ENDING;
                    }
                    

                    char scoreText[10];
                    sprintf(scoreText, "%d", game.score);
                    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

                    DrawTextEx(font, scoreText, {320 + (210 - textSize.x) / 2, 60}, 38, 2, WHITE);
                    
                    
                    game.Draw();

                } break;
                case ENDING:
                {
                    char scoreText[10];
                    sprintf(scoreText, "%d", game.score);
                    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
                    // TODO: Draw ENDING screen here!
                    DrawTexture(texture, screenWidth - texture.width, screenHeight - texture.height, WHITE);
                    DrawTexture(endgame, screenWidth - endgame.width, screenHeight - endgame.height*4, WHITE);
                    DrawTextEx(font, scoreText, {140 + (210 - textSize.x) / 2, 400}, 80, 30, WHITE);
                    DrawTexture(finalpoints, screenWidth - endgame.width, screenHeight - endgame.height*2.5, WHITE);

                } break;
                default: break;
            }

        EndDrawing();
    }


    UnloadTexture(texture);
    UnloadTexture(frame);
    UnloadTexture(endgame);
    UnloadTexture(finalpoints);
    UnloadTexture(pic);
    UnloadTexture(startgame);
    CloseWindow();       


    return 0;
}