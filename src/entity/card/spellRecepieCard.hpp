#pragma once

#include "card.hpp"

class SpellRecepieCard : public Card {
  public:
	SpellRecepieCard();
	~SpellRecepieCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	std::shared_ptr<Spell> spell;
};
