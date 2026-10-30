#pragma once

#include <raylib.h>
#include <vector>

#include "../entity/spell/spell.hpp"

class SpellPage {
  public:
	void Init();

	std::shared_ptr<Spell> UpdateAndGetSelected(PlayerCard &player);
	void Render();

	int width{500};
	int height{700};

	Rectangle rect;

	std::vector<std::shared_ptr<Spell>> spells;

  private:
	void UpdatePosition();
};
