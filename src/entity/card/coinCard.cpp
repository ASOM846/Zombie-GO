#include "coinCard.hpp"
#include "card.hpp"
#include "playerCard.hpp"

CoinCard::CoinCard() {
	name = "COIN";
	value = GetRandomValue(2, 12);
	textureId = TextureId::COIN_0;
}

CoinCard::CoinCard(int p_value) {
	name = "COIN";
	value = p_value;
	textureId = TextureId::COIN_0;
}

void CoinCard::RenderContent(Vector2 offset, Vector2 cellSize,
							 TextureManager &tm) {}

std::string CoinCard::GetValueText() const {
	return std::to_string(value);
}

InteractionResult CoinCard::Interact(PlayerCard &player) {
	player.CollectCoin(value);

	return {.replace = true, .replaceInto = nullptr};
}
