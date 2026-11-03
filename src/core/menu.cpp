#include "menu.hpp"
#include <raylib.h>

void Menu::Init() {
	startGameButton.text = "startGame";

	shouldGameStart = false;

	InitButtonsPositions();
}

void Menu::Update() {
	InitButtonsPositions();
	shouldGameStart = false;

	if (startGameButton.IsClicked(GetMousePosition())) {
		shouldGameStart = true;
	}

	startGameButton.Update(GetMousePosition());
}

void Menu::Render() {
	startGameButton.Draw(GetFontDefault());
}

bool Menu::ShouldGameStart() const {
	return shouldGameStart;
}

void Menu::InitButtonsPositions() {
	Vector2 startButtonSize = {150, 50};
	Vector2 startButtonPos = {
		GetScreenWidth() / 2 - startButtonSize.x / 2,
		GetScreenHeight() / 2 - startButtonSize.y / 2,
	};

	startGameButton.rect = {.x = startButtonPos.x,
							.y = startButtonPos.y,
							.width = startButtonSize.x,
							.height = startButtonSize.y};
}
