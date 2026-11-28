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

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;

	std::shared_ptr<Pickable> pickable;
};
