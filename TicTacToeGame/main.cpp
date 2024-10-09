#include "raylib.h"

int main() {
	InitWindow(600, 600, "Tic Tac Toe");

	SetTargetFPS(60);

	while (!WindowShouldClose) {
		BeginDrawing();
		ClearBackground(BLACK);

		DrawLine(200, 0, 200, 600, WHITE);
		DrawLine(400, 0, 400, 600, WHITE);
		DrawLine(0, 200, 600, 200, WHITE);
		DrawLine(0, 400, 600, 400, WHITE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}