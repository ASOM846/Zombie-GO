#include "spellPage.hpp"
#include <raylib.h>

void SpellPage::Init() {
	// spells.push_back(std::make_shared<HealSpell>());
	// spells.push_back(std::make_shared<DamageSpell>());
	//
	UpdatePosition();
}

std::shared_ptr<Spell> SpellPage::UpdateAndGetSelected(PlayerCard &player) {
	UpdatePosition();

	Vector2 mousePos = GetMousePosition();

	Vector2 offset{rect.x, rect.y};

	Vector2 size{static_cast<float>(width), 150};

	int idx = 0;
	for (auto &spell : player.spells) {

		Vector2 finalPos{offset.x, offset.y + idx * size.y};

		Rectangle spellRect = {finalPos.x, finalPos.y, size.x, size.y};

		if (CheckCollisionPointRec(mousePos, spellRect) &&
			IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			return player.spells[idx];
		}

		idx++;
	}

	return nullptr;
}

void SpellPage::Render(PlayerCard &player) {
	DrawRectangleRec(rect, DARKBROWN);

	Vector2 offset{rect.x, rect.y};

	Vector2 size{static_cast<float>(width), 150};

	int idx = 0;
	for (auto &spell : player.spells) {

		Vector2 finalPos{offset.x, offset.y + idx * size.y};

		spell->Render(finalPos, size);

		idx++;
	}
}

void SpellPage::UpdatePosition() {
	rect = {.x = static_cast<float>(GetScreenWidth() / 2 - width / 2),
			.y = static_cast<float>(GetScreenHeight() / 2 - height / 2),
			.width = static_cast<float>(width),
			.height = static_cast<float>(height)};
}
