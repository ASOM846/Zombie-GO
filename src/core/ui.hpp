#pragma once

#include "../entity/card.hpp"
#include <raylib.h>

class Ui {
  public:
	void Update();
	void Render(std::shared_ptr<PlayerCard> player) {
		float hpPercent =
			static_cast<float>(player->hp) / static_cast<float>(player->maxHp);

		DrawRectangle(100, 100, 300, 50, GREEN);
		DrawRectangle(100, 100, 300 * hpPercent, 50, RED);

		float manaPercent = static_cast<float>(player->mana) /
							static_cast<float>(player->maxMana);

		DrawRectangle(100, 200, 300, 50, DARKGRAY);
		DrawRectangle(100, 200, 300 * manaPercent, 50, ORANGE);
	}
};
