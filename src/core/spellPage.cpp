#include "spellPage.hpp"
#include "../entity/card/playerCard.hpp"
#include <raylib.h>

void SpellPage::Init() {
	UpdatePosition();
}

void SpellPage::Reset() {}

std::shared_ptr<Pickable> SpellPage::UpdateAndGetSelected(PlayerCard &player) {
	UpdatePosition();

	Vector2 mousePos = GetMousePosition();

	Vector2 offset{.x = rect.x, .y = rect.y};

	Vector2 size{static_cast<float>(width), 150};

	int idx = 0;
	for (auto &pickable : player.pickables) {

		Vector2 finalPos{.x = offset.x, .y = offset.y + idx * size.y};

		Rectangle spellRect = {.x = finalPos.x,
							   .y = finalPos.y,
							   .width = size.x,
							   .height = size.y};

		if (CheckCollisionPointRec(mousePos, spellRect) &&
			IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return player.pickables[idx];
		}

		idx++;
	}

	return nullptr;
}

void SpellPage::Render(PlayerCard &player, TextureManager &tm) {
	DrawRectangleRec(rect, DARKGRAY);

	Vector2 offset{rect.x, rect.y};

	Vector2 size{static_cast<float>(width), 150};

	int idx = 0;
	for (auto &pickable : player.pickables) {

		Vector2 finalPos{offset.x, offset.y + idx * size.y};

		pickable->Render(finalPos, size, tm);

		idx++;
	}
}

void SpellPage::UpdatePosition() {
	rect = {.x = static_cast<float>(GetScreenWidth() / 2 - width / 2),
			.y = static_cast<float>(GetScreenHeight() / 2 - height / 2),
			.width = static_cast<float>(width),
			.height = static_cast<float>(height)};
}
