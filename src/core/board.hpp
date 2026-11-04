#pragma once

#include <memory>
#include <raylib.h>
#include <vector>

#include "../entity/card/card.hpp"
#include "../entity/card/playerCard.hpp"
#include "../graphics/screenShake.hpp"
#include "../textureManager.hpp"

class Board {
  public:
	void Init();
	void Reset();

	void Update(ScreenShake &ss);
	void OnActionUpdate(ScreenShake &ss);
	void UpdateHighlights(std::shared_ptr<Spell> selectedSpell);
	void Render(TextureManager &tm);

	void HandleSwipeDown();
	void HandleSwipeUp();
	void HandleSwipeLeft();
	void HandleSwipeRight();

	std::shared_ptr<PlayerCard> GetPlayer();

	std::shared_ptr<Card> GetCellAtPosition(Vector2 posistion);

	Rectangle const &GetTouchRec() { return touchRec; }
	int const &GetSpacing() { return spacing; }
	int const &GetCellWidth() { return cellWidth; }

	void RecalculateDrawindVariables();

  private:
	void RenderCell();

	Vector2 GetPlayerPos();

	std::shared_ptr<Card> GetRandomCard();

	std::vector<std::vector<std::shared_ptr<Card>>> board;

	Rectangle touchRec{};

	const int boardY = 3;
	const int boardX = 3;

	int cellHeight; //= 266; proportions are 1/3 : 1
	int cellWidth;	//=200;

	int maxCellWidth;

	const int spacing = 30;

	Vector2 minOffset{0, 100};
	Vector2 boardOffset{};
};
