#pragma once

#include "card.hpp"

class ActiveEnemyCard : public Card {
  public:
	ActiveEnemyCard();
	~ActiveEnemyCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override;

	Color color;
};
