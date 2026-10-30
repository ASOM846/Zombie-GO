#include <raylib.h>

#include "core/game.hpp"
#include "core/menu.hpp"
#include "core/ui.hpp"

enum class WindowState {
	GAME,
	MENU,
};

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "VaultStep");

	SetTargetFPS(60);

	Menu menu;
	menu.Init();

	Game game;
	game.Init();

	Ui ui;

	WindowState currentState{WindowState::MENU};

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKBLUE);

		switch (currentState) {
		case WindowState::GAME:
			game.Render();

			ui.Render(game.GetBoard().GetPlayer());
			game.Update();
			break;
		case WindowState::MENU:
			menu.Render();
			menu.Update();

			if (menu.ShouldGameStart()) {
				currentState = WindowState::GAME;
			}
			break;
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
