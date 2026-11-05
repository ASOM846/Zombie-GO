#pragma once

#include "card.hpp"

class ActiveEnemyCard : public Card {
  public:
	ActiveEnemyCard();
	~ActiveEnemyCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override;

	Color color;
};
