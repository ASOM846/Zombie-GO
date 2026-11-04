#include "chestCard.hpp"

ChestCard::ChestCard() {
	name = "CHEST";
	textureId = TextureId::CHEST_0;
}

void ChestCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string ChestCard::GetValueText() const {
	return "";
}

bool ChestCard::Interact(PlayerCard &player) {
	return false;
}
