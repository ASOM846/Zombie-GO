#pragma once

#include <raylib.h>
#include <vector>

#include "../entity/card.hpp"
#include "../entity/spell/spell.hpp"

class SpellPage {
  public:
	void Init();

	std::shared_ptr<Spell> UpdateAndGetSelected(PlayerCard &player);
	void Render(PlayerCard &player);

	int width{500};
	int height{700};

	Rectangle rect;

  private:
	void UpdatePosition();
};
