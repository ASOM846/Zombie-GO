#pragma once

#include "card.hpp"

class CoinCard : public Card {
  public:
	CoinCard();
	CoinCard(int value);
	~CoinCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int value;
};
