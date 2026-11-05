#include "playerCard.hpp"

PlayerCard::PlayerCard() {
	name = "PLAYER";

	currentWeapon = std::make_shared<MeleWeaponCard>();
	currentWeapon->name = "SWORD";
	currentWeapon->attack = 5;

	maxHp = 12;

	hp = maxHp;
	coins = 0;

	textureId = TextureId::KNIGHT;
}

void PlayerCard::RenderContent(Vector2 offset, Vector2 cellSize,
							   TextureManager &tm) {}

std::string PlayerCard::GetValueText() const {
	if (currentWeapon)
		return std::string{std::to_string(hp) + "/" + std::to_string(maxHp) +
						   "  |  " + std::to_string(currentWeapon->attack)};

	return std::string{std::to_string(hp) + "/" + std::to_string(maxHp)};
}

bool PlayerCard::Interact(PlayerCard &player) {
	return true;
}
