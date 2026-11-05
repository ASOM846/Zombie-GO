#pragma once

#include <raylib.h>

#include "../entity/card/card.hpp"
#include "../entity/spell/spell.hpp"

class SpellPage {
  public:
	void Init();
	void Reset();

	std::shared_ptr<Pickable> UpdateAndGetSelected(PlayerCard &player);
	void Render(PlayerCard &player);

	int width{500};
	int height{700};

	Rectangle rect;

  private:
	void UpdatePosition();
};
