#include "healthPotionCard.hpp"
#include "playerCard.hpp"

HealthPotionCard::HealthPotionCard() {
	name = "HP POTION";
	amount = GetRandomValue(3, 12);
	textureId = TextureId::FLASK_0;
}

void HealthPotionCard::RenderContent(Vector2 offset, Vector2 cellSize,
									 TextureManager &tm) {}

std::string HealthPotionCard::GetValueText() const {
	return std::to_string(amount);
}

bool HealthPotionCard::Interact(PlayerCard &player) {
	player.hp += amount;

	player.hp = std::min(player.hp, player.maxHp);

	return true;
}
