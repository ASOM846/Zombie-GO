#include "menu.hpp"
#include <raylib.h>

void Menu::Init() {
	startGameButton.text = "Start Game";
	characterSelectButton.text = "Select \n character";
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
	characterSelectButton.Update(GetMousePosition());

	scaleDownButton.Update(GetMousePosition());
	scaleUpButton.Update(GetMousePosition());
}

void Menu::Render() {
	startGameButton.Draw(GetFontDefault());
	characterSelectButton.Draw(GetFontDefault());

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

	const Vector2 bigButtonSize = {150 * gfx::userFontScale,
								   200 * gfx::userFontScale};

	// const float buttonSpacing = buttonSize.x / 2;
	const float buttonSpacing = 40 * gfx::userFontScale;

	characterSelectButton.rect = {
		.x = screenCenterX - buttonSize.x - buttonSpacing / 2.0f,
		.y = screenCenterY - bigButtonSize.y - buttonSpacing,
		.width = bigButtonSize.x,
		.height = bigButtonSize.y};

	startGameButton.rect = {.x = screenCenterX + buttonSpacing / 2.0f,
							.y =
								screenCenterY - bigButtonSize.y - buttonSpacing,
							.width = bigButtonSize.x,
							.height = bigButtonSize.y};

	scaleDownButton.rect = {.x = screenCenterX - buttonSize.x -
								 buttonSpacing / 2.0f,
							.y = screenCenterY - buttonSize.y / 2.0f,
							.width = buttonSize.x,
							.height = buttonSize.y};

	scaleUpButton.rect = {.x = screenCenterX + buttonSpacing / 2.0f,
						  .y = screenCenterY - buttonSize.y / 2.0f,
						  .width = buttonSize.x,
						  .height = buttonSize.y};
}
