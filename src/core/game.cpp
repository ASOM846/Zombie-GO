#include "game.hpp"
#include <algorithm>
#include <memory>
#include <raylib.h>
#include <raymath.h>

void Game::Init() {
	textureManager.loadAll();

	board.Init();
	spellPage.Init();

	currentState = GameState::BOARD;

	spellsButton.text = "SPELLS";
	goBackButton.text = "<";

	UpdateButtonPos();
}

void Game::Reset() {
	currentState = GameState::BOARD;
	spellPage.Reset();
	board.Reset();
}

void Game::Update() {
	board.Update(screenShake);
	board.UpdateHighlights(selectedSpell);
	board.RecalculateDrawindVariables(spellsButton.rect.height);
	screenShake.update(GetFrameTime());

	EffectManager::Get().Update(GetFrameTime());

	gestureInput.Update();

	UpdateButtonPos();

	if (wasActionTaken) {
		board.OnActionUpdate(screenShake);
		wasActionTaken = false;
	}

	if (spellsButton.IsClicked(GetMousePosition())) {
		currentState == GameState::SPELLS ? currentState = GameState::BOARD
										  : currentState = GameState::SPELLS;
	}

	if (goBackButton.IsClicked(GetMousePosition())) {
		currentState = GameState::RETURN_TO_MENU;
	}

	spellsButton.Update(GetMousePosition());
	goBackButton.Update(GetMousePosition());

	switch (currentState) {
	case GameState::BOARD:
		if (CheckCollisionPointRec(gestureInput.GetTouchPointStart(),
								   board.GetTouchRec()) &&
			(gestureInput.GetGestureRecorded() != GESTURE_NONE)) {
			if (gestureInput.GetGestureRecorded() !=
				gestureInput.GetLastGestureRecorded()) {
				switch (gestureInput.GetGestureRecorded()) {
				case GESTURE_SWIPE_DOWN:
					board.HandleSwipeDown();
					wasActionTaken = true;
					break;
				case GESTURE_SWIPE_UP:
					board.HandleSwipeUp();
					wasActionTaken = true;
					break;
				case GESTURE_SWIPE_LEFT:
					board.HandleSwipeLeft();
					wasActionTaken = true;
					break;
				case GESTURE_SWIPE_RIGHT:
					board.HandleSwipeRight();
					wasActionTaken = true;
					break;
				default:
					break;
				}
				screenShake.trigger();
			}
		}

		break;
	case GameState::SPELLS:
		selectedSpell = spellPage.UpdateAndGetSelected(*board.GetPlayer());

		if (selectedSpell != nullptr) {
			currentState = GameState::TARGETTING;
		}

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
				if (selectedSpell->Interact(target)) {
					auto &spells = board.GetPlayer()->pickables;

					auto it =
						std::find(spells.begin(), spells.end(), selectedSpell);

					if (it != spells.end()) {
						spells.erase(it);
					}
				}

				currentState = GameState::BOARD;
				selectedSpell = nullptr;
			}
		}
		break;
	case GameState::RETURN_TO_MENU:
		break;
	}
}

void Game::Render() {
	Camera2D camera = {{0, 0}, {0, 0}, 0.0F, 1.0F};

	camera.offset = screenShake.offset;
	BeginMode2D(camera);

	board.Render(textureManager);

	if (currentState == GameState::SPELLS) {
		spellPage.Render(*board.GetPlayer());
	}

	EndMode2D();

	spellsButton.Draw(GetFontDefault());
	goBackButton.Draw(GetFontDefault());

	// if (selectedSpell) {
	// 	DrawText(selectedSpell->name.c_str(), 100, 300, 30, GREEN);
	// } else {
	// 	DrawText("SPELL NOT SELECTED", 100, 300, 30, GREEN);
	// }

	EffectManager::Get().Draw();

	DrawText(std::to_string(board.GetPlayer()->coins).c_str(),
			 GetScreenWidth() / 2, 40, 45, DARKGREEN);

	if (board.GetPlayer()->hp <= 0) {
		RenderLose();
	}
}

void Game::RenderLose() {
	const float rectangleHeight{100};
	Vector2 recPos{0, (GetScreenHeight() - rectangleHeight) / 2};

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

void Game::UpdateButtonPos() {
	int btnWidth = gfx::cellWidth;
	int btnHeight = 50 * gfx::userFontScale;

	spellsButton.rect = {
		.x = static_cast<float>(GetScreenWidth() / 2 - btnWidth / 2),
		.y = static_cast<float>(GetScreenHeight() - 40 - btnHeight),
		.width = static_cast<float>(btnWidth),
		.height = static_cast<float>(btnHeight)};

	goBackButton.rect = {
		.x = static_cast<float>(GetScreenWidth() / 2 - btnWidth - btnWidth / 2 -
								board.GetSpacing()),
		.y = static_cast<float>(GetScreenHeight() - 40 - btnHeight),
		.width = static_cast<float>(btnWidth),
		.height = static_cast<float>(btnHeight)};
}
