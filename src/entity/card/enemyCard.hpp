#pragma once

#include "card.hpp"

class EnemyCard : public Card {
  public:
	EnemyCard();
	~EnemyCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;

	Color color;
};
