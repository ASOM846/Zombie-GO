#pragma once

#include "card.hpp"
#include <memory>

class Pickable;

class SpellRecepieCard : public Card {
  public:
	SpellRecepieCard();
	~SpellRecepieCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	InteractionResult Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	std::shared_ptr<Pickable> pickable;
};
