#pragma once

#include "card.hpp"

class TrapCard : public Card {
  public:
	TrapCard();
	~TrapCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;

	int attack;
};
