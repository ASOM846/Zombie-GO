#pragma once

#include "card.hpp"

class TrapCard : public Card {
  public:
	TrapCard();
	~TrapCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int attack;
};
