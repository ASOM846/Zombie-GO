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

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	[[nodiscard]] int GetMaxCounterLength() const;
	[[nodiscard]] int GetCurrentCounterLenght() const;

	InteractionResult Interact(PlayerCard &player) override;

	void CollectCoin(int value);

	void Heal(int amount);

	std::shared_ptr<MeleWeaponCard> currentWeapon;

	std::vector<std::shared_ptr<Pickable>> pickables;

	int maxHp;

	int coins;
};
