#include "Rendering.h"

void RenderBoard(char board[3][3], int cellSize) {
    for (int i = 1; i < 3; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, GetScreenHeight(), BLACK);
        DrawLine(0, i * cellSize, GetScreenWidth(), i * cellSize, BLACK);
    }

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] != ' ') {
                DrawMove(board[row][col], row, col, cellSize);
            }
        }
    }
}

void RenderMenu(bool singlePlayer, bool computerMenu) {
    DrawText("Tic Tac Toe", 180, 50, 50, DARKGRAY);
    if (!computerMenu) {
        DrawText("Press '1' for Single Player", 160, 200, 30, DARKGRAY);
        DrawText("Press '2' for Multiplayer", 160, 250, 30, DARKGRAY);
    }
    else {
        DrawText("Select Computer Difficulty", 120, 150, 30, DARKGRAY);
        DrawText("Press '1' for Easy", 160, 200, 30, DARKGRAY);
        DrawText("Press '2' for Medium", 160, 250, 30, DARKGRAY);
        DrawText("Press '3' for Hard", 160, 300, 30, DARKGRAY);
    }
}

void DrawMove(char player, int row, int col, int cellSize) {
    int x = col * cellSize;
    int y = row * cellSize;
    if (player == 'X') {
        DrawLine(x + 20, y + 20, x + cellSize - 20, y + cellSize - 20, RED);
        DrawLine(x + cellSize - 20, y + 20, x + 20, y + cellSize - 20, RED);
    }
    else if (player == 'O') {
        DrawCircle(x + cellSize / 2, y + cellSize / 2, (cellSize / 2.0) - 20, BLUE);
    }
}

void RenderGameOver(char winner, int screenHeight, int screenWidth) {
    if (winner == 'X' || winner == 'O') {
        const char* winnerMessage = (winner == 'D') ? "Draw!" : (winner == 'X') ? "X Wins!" : "O Wins!";
        //DrawText(message, screenWidth / 2 - MeasureText(message, 40) / 2, screenHeight / 2 - 20, 40, RED);
        DrawText(winnerMessage, screenWidth / 2 - MeasureText(winnerMessage, 40) / 2, screenHeight / 2 - 20, 40, RED);
        //DrawText(winnerMessage, 180, 250, 50, DARKGRAY);
    }
    else {
        DrawText("It's a Draw!", 180, 250, 50, DARKGRAY);
    }
    DrawText("Press 'R' to Restart", screenWidth / 2 - 120, screenHeight / 2 + 30, 30, DARKGRAY);
}
