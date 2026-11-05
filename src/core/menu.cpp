#include "menu.hpp"
#include <raylib.h>

void Menu::Init() {
	startGameButton.text = "Start Game";
	scaleUpButton.text = ">";
	scaleDownButton.text = "<";

	shouldGameStart = false;

	InitButtonsPositions();
}

void Menu::Reset() {
	shouldGameStart = false;
}

void Menu::Update() {
	InitButtonsPositions();
	shouldGameStart = false;

	if (startGameButton.IsClicked(GetMousePosition())) {
		shouldGameStart = true;
	}

	if (scaleDownButton.IsClicked(GetMousePosition())) {
		gfx::userFontScale -= 0.10;
	}

	if (scaleUpButton.IsClicked(GetMousePosition())) {
		gfx::userFontScale += 0.10;
	}

	startGameButton.Update(GetMousePosition());
	scaleDownButton.Update(GetMousePosition());
	scaleUpButton.Update(GetMousePosition());
}

void Menu::Render() {
	startGameButton.Draw(GetFontDefault());
	scaleDownButton.Draw(GetFontDefault());
	scaleUpButton.Draw(GetFontDefault());
}

bool Menu::ShouldGameStart() const {
	return shouldGameStart;
}

void Menu::InitButtonsPositions() {
	const float screenCenterX = GetScreenWidth() / 2.0f;
	const float screenCenterY = GetScreenHeight() / 2.0f;

	const Vector2 buttonSize = {150 * gfx::userFontScale,
								50 * gfx::userFontScale};
	const float buttonSpacing = 80.0f * gfx::userFontScale;

	startGameButton.rect = {.x = screenCenterX - buttonSize.x / 2.0f,
							.y = screenCenterY - buttonSize.y / 2.0f,
							.width = buttonSize.x,
							.height = buttonSize.y};

	scaleDownButton.rect = {.x = screenCenterX - buttonSize.x - buttonSpacing,
							.y = screenCenterY - buttonSize.y / 2.0f,
							.width = buttonSize.x,
							.height = buttonSize.y};

	scaleUpButton.rect = {.x = screenCenterX + buttonSpacing,
						  .y = screenCenterY - buttonSize.y / 2.0f,
						  .width = buttonSize.x,
						  .height = buttonSize.y};
}
