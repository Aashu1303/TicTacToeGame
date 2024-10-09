#include "raylib.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time()

// Function to check for a win
bool CheckWin(char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check for a draw
bool CheckDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Function for the computer to make a random move
void ComputerMoveRandom(char board[3][3]) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');
    board[row][col] = 'O';
}

// Function for the computer to make an intelligent move
void ComputerMoveIntelligent(char board[3][3]) {
    // Check if the computer can win in the next move
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                if (CheckWin(board, 'O')) {
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // Check if the player can win in the next move and block them
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'X';
                if (CheckWin(board, 'X')) {
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // If no winning moves, make a random move
    ComputerMoveRandom(board);
}

// Function for the computer to make a corner-first move
void ComputerMoveCornerFirst(char board[3][3]) {
    // List of corners
    int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = 'O';
            return;
        }
    }
    // If no corners available, make a random move
    ComputerMoveRandom(board);
}

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
                            if (computerType == 0) {
                                ComputerMoveRandom(board);
                            }
                            else if (computerType == 1) {
                                ComputerMoveIntelligent(board);
                            }
                            else if (computerType == 2) {
                                ComputerMoveCornerFirst(board);
                            }
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

            // Display game over message
            if (gameOver) {
                const char* message = (currentPlayer == 'D') ? "Draw!" : (currentPlayer == 'X') ? "X Wins!" : "O Wins!";
                DrawText(message, screenWidth / 2 - MeasureText(message, 40) / 2, screenHeight / 2 - 20, 40, RED);
            }

            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}

//The code is well - commented and should be easy to understand.The game uses the  raylib library for graphics and input handling.The game has a simple main menu where you can choose between single - player and multiplayer modes.In single - player mode, you can choose between three different computer types : random, intelligent, and corner - first.The game also has a coin flip to decide who starts first.
//To compile the code, you need to install the raylib library.You can follow the instructions on the  raylib website to install the library on your system.Once you have installed the library, you can compile the code using the following command :
//g++ main.cpp - o TicTacToeGame - lraylib - lGL - lm - lpthread - ldl - lrt - lX11
//
//This will create an executable file named  TicTacToeGame.You can run the game by executing the following command :
//. / TicTacToeGame
//
//The game should open in a resizable window, and you can play by clicking on the squares to place your marks.You can press the spacebar to flip a coin to decide who starts first.
//I hope this helps!Let me know if you have any questions.
//I am trying to create a simple Tic Tac Toe game in C++ using the raylib library.I have created a 3x3 grid and I am able to draw the grid and the marks(X and O) on the grid.I am also able to handle mouse input to place the marks on the grid.However, I am having trouble implementing the logic to check for a win or a draw in the game.Can you help me with the logic to check for a win or a draw in a Tic Tac Toe game ?
//To check for a win or a draw in a Tic Tac Toe game, you need to check the rows, columns, and diagonals of the grid to see if there are three consecutive marks of the same type(X or O).You also need to check if all the squares on the grid are filled to determine if the game is a draw.Here is the logic to check for a win or a draw in a Tic Tac Toe game :
// Function to check for a win
