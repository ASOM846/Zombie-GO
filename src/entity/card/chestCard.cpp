#include "chestCard.hpp"
#include "card.hpp"
#include "coinCard.hpp"

ChestCard::ChestCard() {
	name = "CRATE";
	textureId = TextureId::CRATE_0;
}

void ChestCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string ChestCard::GetTopText() const {
	return name;
}

std::string ChestCard::GetBottomText() const {
	return "";
}

InteractionResult ChestCard::Interact(PlayerCard &player) {
	return {.replace = true, .replaceInto = std::make_shared<CoinCard>()};
}
