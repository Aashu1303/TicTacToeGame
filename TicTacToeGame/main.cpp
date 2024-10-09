#include "raylib.h"
#include "Rendering.h"
#include "GameLogic.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()


static bool first = false;


int main() {
    InitWindow(600, 600, "Tic Tac Toe");
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Make the window resizable
    SetTargetFPS(60);
    srand(time(NULL)); // Seed the random number generator

    char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char currentPlayer = 'X';
    bool gameOver = false;
    bool singlePlayer = false;
    bool menu = true;
    bool computerMenu = false;
    int computerType = 0; // 0 for random, 1 for intelligent, 2 for corner-first
    bool coinFlip = true;

    while (!WindowShouldClose()) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int cellSize = screenWidth / 3;

        if (menu) {
            // Handle main menu input
            if (IsKeyPressed(KEY_ONE)) {
                singlePlayer = true;
                menu = false;
                computerMenu = true;
            }
            else if (IsKeyPressed(KEY_TWO)) {
                singlePlayer = false;
                menu = false;
            }

            // Draw main menu
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Tic Tac Toe", screenWidth / 2 - MeasureText("Tic Tac Toe", 40) / 2, 100, 40, WHITE);
            DrawText("Press 1 for Single Player", screenWidth / 2 - MeasureText("Press 1 for Single Player", 30) / 2, 200, 30, WHITE);
            DrawText("Press 2 for Multiplayer", screenWidth / 2 - MeasureText("Press 2 for Multiplayer", 30) / 2, 300, 30, WHITE);
            EndDrawing();
        }
        else if (computerMenu) {

            // Handle computer menu input

            if (IsKeyPressed(KEY_ONE)) {
                computerType = 0;
                computerMenu = false;
            }
            else if (IsKeyPressed(KEY_TWO)) {
                computerType = 1;
                computerMenu = false;
            }
            else if (IsKeyPressed(KEY_THREE)) {
                computerType = 2;
                computerMenu = false;
            }

            // Draw computer menu
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Choose Computer Type", screenWidth / 2 - MeasureText("Choose Computer Type", 40) / 2, 100, 40, WHITE);
            DrawText("Press 1 for Random", screenWidth / 2 - MeasureText("Press 1 for Random", 30) / 2, 200, 30, WHITE);
            DrawText("Press 2 for Intelligent", screenWidth / 2 - MeasureText("Press 2 for Intelligent", 30) / 2, 300, 30, WHITE);
            DrawText("Press 3 for Corner-First", screenWidth / 2 - MeasureText("Press 3 for Corner-First", 30) / 2, 400, 30, WHITE);
            EndDrawing();
        }
        else if (coinFlip) {
            // Coin flip to decide who starts
            if (IsKeyPressed(KEY_SPACE)) {
                currentPlayer = (rand() % 2 == 0) ? 'X' : 'O';
                if (currentPlayer == 'O')
                {
                    first == true;
                }
                coinFlip = false;
            }

            // Draw coin flip screen
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Press SPACE to Flip Coin", screenWidth / 2 - MeasureText("Press SPACE to Flip Coin", 30) / 2, 200, 30, WHITE);
            EndDrawing();
        }
        else {
            // Handle input
            if (currentPlayer == 'O' && first) {
				ComputerMove(board, currentPlayer, computerType);
                
                if (CheckWin(board, 'O')) {
                    gameOver = true;
                }
                else if (CheckDraw(board)) {
                    gameOver = true;
                    currentPlayer = 'D'; // Draw
                }
                else {
                    currentPlayer = 'X';
                }
                first = false;
				continue;
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !gameOver) {
                Vector2 mousePos = GetMousePosition();
                int row = mousePos.y / cellSize;
                int col = mousePos.x / cellSize;

                if (board[row][col] == ' ') {
                    board[row][col] = currentPlayer;
                    if (CheckWin(board, currentPlayer)) {
                        gameOver = true;
                    }
                    else if (CheckDraw(board)) {
                        gameOver = true;
                        currentPlayer = 'D'; // Draw
                    }
                    else {
                        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                        if (singlePlayer && currentPlayer == 'O' && !gameOver) {
							ComputerMove(board, currentPlayer, computerType);
                            if (CheckWin(board, 'O')) {
                                gameOver = true;
                            }
                            else if (CheckDraw(board)) {
                                gameOver = true;
                                currentPlayer = 'D'; // Draw
                            }
                            else {
                                currentPlayer = 'X';
                            }
                        }
                    }
                }
            }

            // Draw
            BeginDrawing();
            ClearBackground(BLACK);

            // Draw grid
            for (int i = 1; i < 3; i++) {
                DrawLine(i * cellSize, 0, i * cellSize, screenHeight, WHITE);
                DrawLine(0, i * cellSize, screenWidth, i * cellSize, WHITE);
            }

            // Draw marks
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == 'X') {
                        DrawLine(j * cellSize, i * cellSize, (j + 1) * cellSize, (i + 1) * cellSize, WHITE);
                        DrawLine((j + 1) * cellSize, i * cellSize, j * cellSize, (i + 1) * cellSize, WHITE);
                    }
                    else if (board[i][j] == 'O') {
                        DrawCircle((j * cellSize) + cellSize / 2, (i * cellSize) + cellSize / 2, cellSize / 2 - 10, WHITE);
                    }
                }
            }
            EndDrawing();
            // Display game over message

        }
        
        while (gameOver) {
            BeginDrawing();
            ClearBackground(BLACK);
            RenderGameOver(currentPlayer, screenHeight, screenWidth);
            EndDrawing();
            if (IsKeyPressed(KEY_R)) {
                ResetBoard(board);
                gameOver = false;
                coinFlip = true;
                menu = true;
                first = true;
            }
        }
    }

    CloseWindow();
    return 0;
}