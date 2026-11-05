#pragma once

#include <raylib.h>

#include "../graphics/floatingText.hpp"
#include "../graphics/screenShake.hpp"
#include "../textureManager.hpp"
#include "board.hpp"
#include "button.hpp"
#include "gestureInput.hpp"
#include "spellPage.hpp"

enum class GameState {
	BOARD,
	SPELLS,
	TARGETTING,

	RETURN_TO_MENU,
};

class Game {
  public:
	void Init();
	void Reset();

	void Update();
	void Render();

	Board &GetBoard() { return board; };

	TextureManager *GetTextureManager() { return &textureManager; }

	GameState &GetCurrentState() { return currentState; }

  private:
	void RenderLose();
	void UpdateButtonPos();
	GameState currentState;

	Board board;

	GestureInput gestureInput;

	SpellPage spellPage;

	Button spellsButton;
	Button goBackButton;

	std::shared_ptr<Pickable> selectedSpell{nullptr};

	bool wasActionTaken;

	TextureManager textureManager;
	ScreenShake screenShake;
};
