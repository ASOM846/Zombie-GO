#include "game.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <raymath.h>

void Game::Init() {
	TraceLog(LOG_WARNING, "GAME INIT START");

	TraceLog(LOG_WARNING, "WORKING DIR: %s", GetWorkingDirectory());

	TraceLog(LOG_WARNING, "KNIGHT EXISTS: %d",
			 FileExists("assets/knight0.png"));

	TraceLog(LOG_WARNING, "TEXTURES LOADED");

	textureManager.loadAll();

	board.Init();
	spellPage.Init();

	currentState = GameState::BOARD;

	spellsButton.text = "SPELLS";
}

int Game::InterpreateGesture() {
	Vector2 diff = Vector2Subtract(touchEndPos, touchStartPos);

	if (std::abs(diff.x) > std::abs(diff.y)) {
		return diff.x > 0 ? GESTURE_SWIPE_RIGHT : GESTURE_SWIPE_LEFT;
	}

	return diff.y > 0 ? GESTURE_SWIPE_DOWN : GESTURE_SWIPE_UP;
}

void Game::Update() {
	lastGesture = currentGesture;
	touchArea = {.x = 0,
				 .y = 0,
				 .width = static_cast<float>(GetRenderWidth()),
				 .height = static_cast<float>(GetRenderHeight())};

	board.Update(screenShake);
	screenShake.update(GetFrameTime());

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		touchStartPos = GetMousePosition();
		std::cout << "1 position registered\n";
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		touchEndPos = GetMousePosition();
		currentGesture = InterpreateGesture();
		lastGesture = -1;
		std::cout << "3 position interpreted\n";
	}

	if (wasActionTaken) {
		board.OnActionUpdate(screenShake);
		wasActionTaken = false;
	}

	int btnWidth = 100;
	int btnHeight = 50;
	spellsButton.rect = {
		.x = static_cast<float>(GetScreenWidth() / 2 - btnWidth / 2),
		.y = static_cast<float>(GetScreenHeight() - 40 - btnHeight),
		.width = static_cast<float>(btnWidth),
		.height = static_cast<float>(btnHeight)};

	if (spellsButton.IsClicked(GetMousePosition())) {
		currentState == GameState::SPELLS ? currentState = GameState::BOARD
										  : currentState = GameState::SPELLS;
	}

	if (IsKeyPressed(KEY_M)) {
		screenShake.trigger();
	}

	switch (currentState) {
	case GameState::BOARD:
		if (CheckCollisionPointRec(touchStartPos, touchArea) &&
			(currentGesture != GESTURE_NONE)) {
			if (currentGesture != lastGesture) {
				switch (currentGesture) {
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
				}
			}
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
				if (selectedSpell->Interact(target)) {
					auto &spells = board.GetPlayer()->spells;

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
	}
}

void Game::Render() {
	Camera2D camera = {{0, 0}, {0, 0}, 0.0f, 1.0f};

	camera.offset = screenShake.offset;
	BeginMode2D(camera);

	board.Render(textureManager);

	if (currentState == GameState::SPELLS)
		spellPage.Render(*board.GetPlayer());

	EndMode2D();

	spellsButton.Draw(GetFontDefault());

	if (selectedSpell)
		DrawText(selectedSpell->name.c_str(), 100, 300, 30, GREEN);
	else
		DrawText("SPELL NOT SELECTED", 100, 300, 30, GREEN);

	if (board.GetPlayer()->hp <= 0) {
		RenderLose();
	}
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
