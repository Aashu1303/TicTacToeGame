#pragma once
#include "raylib.h"
#include <stdio.h>

// Function to render the Tic Tac Toe board
void RenderBoard(char board[3][3], int cellSize);

// Function to render the game menu
void RenderMenu(bool singlePlayer, bool computerMenu);

// Function to draw X or O at a specific board position
void DrawMove(char player, int row, int col, int cellSize);

// Function to display game-over screen
void RenderGameOver(char winner, int screenHeight, int screenWidth);