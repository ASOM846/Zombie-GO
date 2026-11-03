#pragma once

#include <raylib.h>

#include "../graphics/screenShake.hpp"
#include "../textureManager.hpp"
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

	int InterpreateGesture();

	void Update();
	void Render();

	Board &GetBoard() { return board; };

	TextureManager *GetTextureManager() { return &textureManager; }

	Vector2 touchStartPos;
	Vector2 touchEndPos;

	Rectangle touchArea{0, 0, 1920, 1080};

  private:
	void RenderLose();

	GameState currentState;

	Board board;

	SpellPage spellPage;
	Button spellsButton;

	int currentGesture;
	int lastGesture;

	std::shared_ptr<Spell> selectedSpell{nullptr};

	bool wasActionTaken;

	TextureManager textureManager;
	ScreenShake screenShake;
};
