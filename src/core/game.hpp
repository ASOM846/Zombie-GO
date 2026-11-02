#pragma once

#include <raylib.h>

#include "board.hpp"
#include "button.hpp"
#include "spellPage.hpp"
#include "textureManager.hpp"

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

	Vector2 touchPosition{0, 0};
	int currentGesture{GESTURE_NONE};
	int lastGesture{GESTURE_NONE};
	Rectangle touchArea{0, 0, 1920, 1080};

  private:
	void RenderLose();

	GameState currentState;

	Board board;

	SpellPage spellPage;
	Button spellsButton;

	std::shared_ptr<Spell> selectedSpell{nullptr};

	TextureManager textureManager;
};
