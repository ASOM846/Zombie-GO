#include <raylib.h>

#include "core/game.hpp"

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "VaultStep");

	SetTargetFPS(60);

	Game game;

	game.Init();

	while (!WindowShouldClose()) {
		BeginDrawing();

		game.Render();

		ClearBackground(BLACK);

		game.Update();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
