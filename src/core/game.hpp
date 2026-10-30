#pragma once

#include <raylib.h>

#include "board.hpp"
#include "button.hpp"
#include "spellPage.hpp"

enum class GameState {
	BOARD,
	SPELLS,
	TARGETTING,
};

class Game {
  public:
	void Init();

	void Update();
	void Render();

	Board &GetBoard() { return board; };

  private:
	GameState currentState;

	Board board;

	SpellPage spellPage;
	Button spellsButton;

	std::shared_ptr<Spell> selectedSpell{nullptr};
};
