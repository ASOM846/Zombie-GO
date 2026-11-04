#include "coinCard.hpp"
#include "playerCard.hpp"

CoinCard::CoinCard() {
	name = "COIN";
	value = GetRandomValue(2, 12);
	textureId = TextureId::COIN_0;
}

void CoinCard::RenderContent(Vector2 offset, Vector2 cellSize,
							 TextureManager &tm) {}

std::string CoinCard::GetValueText() const {
	return std::to_string(value);
}

bool CoinCard::Interact(PlayerCard &player) {
	player.coins += value;
	return true;
}
