#include <raylib.h>

#include "core/game.hpp"
#include "core/menu.hpp"
#include "core/ui.hpp"
#include "graphics/fpsGraph.hpp"

enum class WindowState {
	GAME,
	MENU,
};

void DrawBackground(const Texture2D &tex) {
	Rectangle src{0, 0, static_cast<float>(tex.width),
				  static_cast<float>(tex.height)};
	Rectangle dst{0, 0, static_cast<float>(GetScreenWidth()),
				  static_cast<float>(GetScreenHeight())};

	DrawTexturePro(tex, src, dst, {0, 0}, 0.0f, WHITE);
}

void SwitchState(WindowState &currentState, WindowState newState) {}

int main() {
	int screenHeight = 1080; // static_cast<int>(screenWidth * 19.5f / 9.0f);
	int screenWidth = static_cast<int>(screenHeight * 9.0f / 19.5f);

	// #if defined(__ANDROID__)
	// 	width = height = 0;
	// #endif

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetWindowState(FLAG_VSYNC_HINT);

	InitWindow(screenWidth, screenHeight, "VaultStep");

	SetTargetFPS(60);
	initFPSGraph(60, 300, 150);

	Menu menu;
	menu.Init();

	Game game;
	game.Init();

	Ui ui;

	WindowState currentState{WindowState::MENU};

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKBLUE);

		DrawBackground(game.GetTextureManager()->get(TextureId::BCG_0));
		DrawBackground(game.GetTextureManager()->get(TextureId::VIGNETTE_0));

		auto switchState = [&currentState, &game, &menu](WindowState newState) {
			if (currentState == newState) {
				return;
			}

			switch (newState) {
			case WindowState::GAME:
				game.Reset();
				break;
			case WindowState::MENU:
				menu.Reset();
				break;
			}

			currentState = newState;
		};

		switch (currentState) {
		case WindowState::GAME:
			game.Update();
			if (game.GetCurrentState() == GameState::RETURN_TO_MENU) {
				switchState(WindowState::MENU);
			}
			break;
		case WindowState::MENU:
			menu.Update();

			if (menu.ShouldGameStart()) {
				switchState(WindowState::GAME);
			}
			break;
		}

		switch (currentState) {
		case WindowState::GAME:
			game.Render();

			ui.Render(game.GetBoard().GetPlayer());
			break;
		case WindowState::MENU:
			menu.Render();

			break;
		}
		tickFPSGraph(GetFPS());
		drawFPSGraph(0, 0);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
