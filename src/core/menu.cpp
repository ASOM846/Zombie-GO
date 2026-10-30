#include "menu.hpp"
#include <raylib.h>

void Menu::Init() {
	startGameButton.rect = {.x = 200, .y = 200, .width = 100, .height = 100};

	startGameButton.text = "startGame";

	shouldGameStart = false;
}

void Menu::Update() {
	shouldGameStart = false;

	if (startGameButton.IsClicked(GetMousePosition())) {
		shouldGameStart = true;
	}
}

void Menu::Render() {
	startGameButton.Draw(GetFontDefault());
}

bool Menu::ShouldGameStart() {
	return shouldGameStart;
}
