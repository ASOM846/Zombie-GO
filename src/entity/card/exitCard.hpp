#pragma once

#include "card.hpp"
#include <raylib.h>

class ExitCard : public Card {
  public:
	ExitCard();
	~ExitCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetTopText() const override;
	[[nodiscard]] std::string GetBottomText() const override;

	InteractionResult Interact(PlayerCard &player) override;
};
