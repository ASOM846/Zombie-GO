#pragma once

#include "card.hpp"
#include "weaponCard.hpp"
#include <memory>
#include <vector>

class Pickable;

class PlayerCard : public Card {
  public:
	PlayerCard();
	~PlayerCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	void CollectCoin(int value);

	std::shared_ptr<MeleWeaponCard> currentWeapon;

	std::vector<std::shared_ptr<Pickable>> pickables;

	int maxHp;

	int coins;
};
