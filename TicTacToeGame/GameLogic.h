#pragma once

bool CheckWin(char board[3][3], char player);
bool CheckDraw(char board[3][3]);
void ComputerMoveRandom(char board[3][3]);
void ComputerMoveIntelligent(char board[3][3]);
void ComputerMoveCornerFirst(char board[3][3]);
void ResetBoard(char board[3][3]);
char CoinFlip();
void ComputerMove(char board[3][3], char player, int difficulty);