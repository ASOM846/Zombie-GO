#pragma once

#include <memory>
#include <raylib.h>
#include <vector>

#include "../entity/card.hpp"
#include "textureManager.hpp"

class Board {
  public:
	void Init();

	void Update();
	void Render(TextureManager &tm);

	void HandleSwipeDown();
	void HandleSwipeUp();
	void HandleSwipeLeft();
	void HandleSwipeRight();

	std::shared_ptr<PlayerCard> GetPlayer();

	std::shared_ptr<Card> GetCellAtPosition(Vector2 posistion);

  private:
	void RenderCell();

	Vector2 GetPlayerPos();

	std::shared_ptr<Card> GetRandomCard();

	std::vector<std::vector<std::shared_ptr<Card>>> board;

	const int boardY = 3;
	const int boardX = 3;

	int cellHeight = 266;
	int cellWidth = 200;

	const int spacing = 30;
};
