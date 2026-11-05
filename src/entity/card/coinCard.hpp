#pragma once

#include "card.hpp"

class CoinCard : public Card {
  public:
	CoinCard();
	CoinCard(int value);
	~CoinCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int value;
};
