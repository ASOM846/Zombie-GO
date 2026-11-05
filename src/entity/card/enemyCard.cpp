#include "enemyCard.hpp"
#include "../../graphics/floatingText.hpp"
#include "../../graphics/gfx.hpp"
#include "card.hpp"
#include "coinCard.hpp"
#include "playerCard.hpp"
#include <memory>
#include <string>
#include <vector>

EnemyCard::EnemyCard() {
	hp = GetRandomValue(1, 6);
	name = "ENEMY";

	auto GetRandomTexture = []() {
		std::vector<TextureId> textures{TextureId::ENEMY_0, TextureId::ENEMY_1,
										TextureId::ENEMY_2, TextureId::ENEMY_3,
										TextureId::ENEMY_4, TextureId::ENEMY_5};

		int seed = GetRandomValue(0, textures.size() - 1);

		return textures[seed];
	};

	textureId = GetRandomTexture();
}

void EnemyCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string EnemyCard::GetValueText() const {
	return std::to_string(hp);
}

InteractionResult EnemyCard::Interact(PlayerCard &player) {
	int playerDmg = 0;
	int startHp = hp;

	if (player.currentWeapon && player.currentWeapon->attack > 0) {
		playerDmg = player.currentWeapon->attack;

		player.currentWeapon->attack -= hp;
		TakeDamage(playerDmg);

		if (player.currentWeapon->attack <= 0) {
			player.currentWeapon->attack = 0;
			player.currentWeapon.reset();
		}
	} else {
		playerDmg = player.hp;

		player.hp -= hp;
		TakeDamage(playerDmg);

		if (player.hp < 0)
			player.hp = 0;
	}

	if (hp > 0) {
		return {.replace = false, .replaceInto = nullptr};
	}

	return {.replace = true,
			.replaceInto = std::make_shared<CoinCard>(startHp)};
}
