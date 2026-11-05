#include "playerCard.hpp"

#include "../../graphics/floatingText.hpp"
#include "card.hpp"
#include <raylib.h>

PlayerCard::PlayerCard() {
	name = "SURVIVOR";

	currentWeapon = std::make_shared<MeleWeaponCard>();

	maxHp = 10;

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

InteractionResult PlayerCard::Interact(PlayerCard &player) {
	return {.replace = true, .replaceInto = nullptr};
}

void PlayerCard::CollectCoin(int value) {
	coins += value;

	EffectManager::Get().SpawnText(
		{static_cast<float>(GetScreenWidth() / 2), 40},
		"+" + std::to_string(value), DARKGREEN);
}
