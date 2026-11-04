#pragma once

#include "card.hpp"
#include "weaponCard.hpp"
#include <memory>
#include <vector>

class PlayerCard : public Card {
  public:
	PlayerCard();
	~PlayerCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	std::shared_ptr<MeleWeaponCard> currentWeapon;

	std::vector<std::shared_ptr<Spell>> spells;

	int maxHp;

	int coins;
};
