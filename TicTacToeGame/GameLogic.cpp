#include "GameLogic.h"
#include <stdlib.h> // For rand() and srand()

// Check if the given player has won the game
bool CheckWin(char board[3][3], char player) {
    // Check rows and csolumns
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

void ResetBoard(char board[3][3]) {
    // Initialize or reset the board to be empty
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

char CoinFlip() {
    // Randomly select either 'X' or 'O' to go first
    return (rand() % 2 == 0) ? 'X' : 'O';
}

// Check if the game is a draw
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

// Random move for the computer
void ComputerMoveRandom(char board[3][3]) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' '); // Keep generating until an empty cell is found
    board[row][col] = 'O'; // Computer plays as 'O'
}

// Intelligent move logic using a simple strategy
void ComputerMoveIntelligent(char board[3][3]) {
    // Check if the computer can win in the next move
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == ' ') {
                board[row][col] = 'O'; // Temporarily make the move
                if (CheckWin(board, 'O')) {
                    return; // If it wins, play here
                }
                board[row][col] = ' '; // Undo the move
            }
        }
    }
    // Block the opponent's winning move
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row][col] == ' ') {
                board[row][col] = 'X'; // Temporarily simulate opponent's move
                if (CheckWin(board, 'X')) {
                    board[row][col] = 'O'; // Block the opponent
                    return;
                }
                board[row][col] = ' '; // Undo the move
            }
        }
    }
    // If no winning or blocking moves, fall back to random move
    ComputerMoveRandom(board);
}

// Move strategy prioritizing corners
void ComputerMoveCornerFirst(char board[3][3]) {
    int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (board[row][col] == ' ') {
            board[row][col] = 'O'; // Play in a corner if available
            return;
        }
    }
    // If no corner is available, make a random move
    ComputerMoveRandom(board);
}

// Computer move based on the selected difficulty level
void ComputerMove(char board[3][3], char player, int difficulty) {
	if (difficulty == 0) {
		ComputerMoveRandom(board);
	}
	else if (difficulty == 1) {
		ComputerMoveIntelligent(board);
	}
	else if (difficulty == 2) {
		ComputerMoveCornerFirst(board);
	}
}