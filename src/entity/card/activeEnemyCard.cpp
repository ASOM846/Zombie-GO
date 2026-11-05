#include "activeEnemyCard.hpp"
#include "card.hpp"
#include "coinCard.hpp"
#include "playerCard.hpp"

ActiveEnemyCard::ActiveEnemyCard() {
	hp = GetRandomValue(1, 6);
	name = "ACTIVE ENEMY";

	auto GetRandomTexture = []() {
		std::vector<TextureId> textures{TextureId::ACTIVE_ENEMY_0};

		int seed = GetRandomValue(0, textures.size() - 1);

		return textures[seed];
	};

	textureId = GetRandomTexture();
	gradientColor = RED;
}

void ActiveEnemyCard::RenderContent(Vector2 offset, Vector2 cellSize,
									TextureManager &tm) {}

std::string ActiveEnemyCard::GetValueText() const {
	return std::to_string(hp);
}

InteractionResult ActiveEnemyCard::Interact(PlayerCard &player) {
	int playerDmg = 0;

	if (player.currentWeapon && player.currentWeapon->attack > 0) {
		playerDmg = player.currentWeapon->attack;

		player.currentWeapon->attack -= hp;
		hp -= playerDmg;

		if (player.currentWeapon->attack <= 0) {
			player.currentWeapon->attack = 0;
			player.currentWeapon.reset();
		}
	} else {
		playerDmg = player.hp;

		player.hp -= hp;
		hp -= playerDmg;

		if (player.hp < 0)
			player.hp = 0;
	}

	if (hp > 0) {
		return {.replace = false, .replaceInto = nullptr};
	}

	return {.replace = true, .replaceInto = std::make_shared<CoinCard>()};
}

void ActiveEnemyCard::AutoAction(PlayerCard &player) {
	hp += 1;
	if (GetRandomValue(1, 2) == 1)
		player.hp -= 1;
}
