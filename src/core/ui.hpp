#pragma once

#include "../entity/card/card.hpp"
#include <raylib.h>

class Ui {
  public:
	void Update();
	void Render(const std::shared_ptr<PlayerCard> &player) {
		float hpPercent =
			static_cast<float>(player->hp) / static_cast<float>(player->maxHp);

		DrawRectangle(100, 100, 300, 50, GREEN);
		DrawRectangle(100, 100, 300 * hpPercent, 50, RED);

		hpPercent *= 100;
		DrawText(std::to_string(static_cast<int>(hpPercent)).c_str(), 100, 100,
				 30, MAGENTA);
	}
};
