#include "game.hpp"
#include <raylib.h>

void Game::Init() {
	board.Init();
	spellPage.Init();

	currentState = GameState::BOARD;

	spellsButton.text = "SPELLS";
}

void Game::Update() {
	board.Update();

	int btnWidth = 100;
	int btnHeight = 50;
	spellsButton.rect = {
		.x = static_cast<float>(GetScreenWidth() / 2 - btnWidth / 2),
		.y = static_cast<float>(GetScreenHeight() - 40 - btnHeight),
		.width = static_cast<float>(btnWidth),
		.height = static_cast<float>(btnHeight)};

	if (IsKeyPressed(KEY_M) || spellsButton.IsClicked(GetMousePosition())) {
		currentState == GameState::SPELLS ? currentState = GameState::BOARD
										  : currentState = GameState::SPELLS;
	}

	switch (currentState) {
	case GameState::BOARD:
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

		break;
	case GameState::SPELLS:
		selectedSpell = spellPage.UpdateAndGetSelected(*board.GetPlayer());

		if (selectedSpell != nullptr)
			currentState = GameState::TARGETTING;

		break;
	case GameState::TARGETTING:
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			std::shared_ptr<Card> target =
				board.GetCellAtPosition(GetMousePosition());

			if (target == nullptr) {
				currentState = GameState::BOARD;
				selectedSpell = nullptr;
			}

			if (target != nullptr && selectedSpell != nullptr) {
				selectedSpell->Interact(target);
				board.GetPlayer()->mana -= selectedSpell->manaRequired;
				currentState = GameState::BOARD;
				selectedSpell = nullptr;
			}
		}
		break;
	}

	if (board.GetPlayer()->hp <= 0) {
		RenderLose();
	}
}

void Game::Render() {
	board.Render();

	if (currentState == GameState::SPELLS)
		spellPage.Render();

	spellsButton.Draw(GetFontDefault());

	if (selectedSpell)
		DrawText(selectedSpell->name.c_str(), 100, 300, 30, GREEN);
	else
		DrawText("SPELL NOT SELECTED", 100, 300, 30, GREEN);
}

void Game::RenderLose() {
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
