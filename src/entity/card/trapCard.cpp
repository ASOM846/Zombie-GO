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

std::string TrapCard::GetTopText() const {
	return name;
}

std::string TrapCard::GetBottomText() const {
	return std::to_string(attack);
}

InteractionResult TrapCard::Interact(PlayerCard &player) {
	player.TakeDamage(attack);

	return {.replace = true, .replaceInto = nullptr};
}
