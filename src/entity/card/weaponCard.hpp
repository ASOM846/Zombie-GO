#pragma once

#include "card.hpp"

class MeleWeaponCard : public Card {
  public:
	MeleWeaponCard();
	~MeleWeaponCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int minAttack;
	int maxAttack;

	int currentDurability;
	int maxDurability;
};
