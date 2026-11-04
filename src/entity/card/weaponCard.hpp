#pragma once

#include "card.hpp"

class SwordCard : public Card {
  public:
	SwordCard();
	~SwordCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int attack;
};
