#pragma once

#include "../entity/card/playerCard.hpp"
#include <raylib.h>
#include <string>

class Ui {
  public:
	void Update();
	void Render(const std::shared_ptr<PlayerCard> &player, int actionsTaken,
				int actionsToTake) {
		float hpPercent =
			static_cast<float>(player->hp) / static_cast<float>(player->maxHp);

		DrawRectangle(100, 100, 300, 50, GREEN);
		DrawRectangle(100, 100, 300 * hpPercent, 50, RED);

		hpPercent *= 100;
		DrawText(std::to_string(static_cast<int>(hpPercent)).c_str(), 100, 100,
				 30, MAGENTA);

		std::string actions{std::to_string(actionsTaken) + "/" +
							std::to_string(actionsToTake)};

		DrawText(actions.c_str(), 100, 200, 30, MAGENTA);
	}
};
