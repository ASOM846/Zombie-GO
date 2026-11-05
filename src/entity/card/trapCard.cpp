#include "trapCard.hpp"
#include "card.hpp"
#include "playerCard.hpp"

TrapCard::TrapCard() {
	name = "TRAP";
	attack = GetRandomValue(1, 8);
	textureId = TextureId::TRAP_0;
}

void TrapCard::RenderContent(Vector2 offset, Vector2 cellSize,
							 TextureManager &tm) {}

std::string TrapCard::GetValueText() const {
	return std::to_string(attack);
}

InteractionResult TrapCard::Interact(PlayerCard &player) {
	player.hp -= attack;

	return {.replace = true, .replaceInto = nullptr};
}
