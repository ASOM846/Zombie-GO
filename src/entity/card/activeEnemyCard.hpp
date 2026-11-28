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

	[[nodiscard]] int GetMaxCounterLength() const;
	[[nodiscard]] int GetCurrentCounterLenght() const;

	InteractionResult Interact(PlayerCard &player) override;
	InteractionResult AutoAction(PlayerCard &player) override;

	Color color;

	int toAttackCounter;
	int turnsToAttack;
};
