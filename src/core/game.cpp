#include "game.hpp"
#include "../entity/card.hpp"
#include <raylib.h>

void Game::Init() {
	board.Init();
}

void Game::Update() {
	board.Update();

	if (IsKeyPressed(KEY_DOWN)) {
		board.HandleSwipeDown();
	}

	if (IsKeyPressed(KEY_UP)) {
		board.HandleSwipeUp();
	}

	if (IsKeyPressed(KEY_LEFT)) {
		board.HandleSwipeLeft();
	}

	if (IsKeyPressed(KEY_RIGHT)) {
		board.HandleSwipeRight();
	}

	if (board.GetPlayer()->hp <= 0) {
		float rectangleHeight{100};
		Vector2 recPos{0, {(GetScreenHeight() - rectangleHeight) / 2}};

		DrawRectangleV(recPos,
					   {static_cast<float>(GetScreenWidth()), rectangleHeight},
					   ColorAlpha(BLACK, 0.5));

		std::string text{"GAME LOST"};

		int fontSize = 60;
		int spacing = 4;

		Vector2 textSize =
			MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing);

		Vector2 finalPos{{(GetScreenWidth() - textSize.x) / 2},
						 {(GetScreenHeight() - textSize.y) / 2}};

		DrawTextEx(GetFontDefault(), text.c_str(), finalPos, fontSize, spacing,
				   RED);
	}
}

void Game::Render() {
	board.Render();
}
