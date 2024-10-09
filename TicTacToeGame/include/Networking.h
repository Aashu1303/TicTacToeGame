#pragma once

void InitMultiplayer();
void SendMove(int row, int col);
void ReceiveMove(int& row, int& col);
void CloseMultiplayer();
