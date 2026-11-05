#include "enemyCard.hpp"
#include "card.hpp"
#include "coinCard.hpp"
#include "playerCard.hpp"
#include <memory>
#include <raylib.h>
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

std::string EnemyCard::GetTopText() const {
	return {name};
}

std::string EnemyCard::GetBottomText() const {
	return std::to_string(hp);
}

InteractionResult EnemyCard::Interact(PlayerCard &player) {
	int playerDmg = 0;
	int startHp = hp;

	if (player.currentWeapon && player.currentWeapon->currentDurability > 0) {
		playerDmg = GetRandomValue(player.currentWeapon->minAttack,
								   player.currentWeapon->maxAttack);

		TakeDamage(playerDmg);

		player.currentWeapon->currentDurability -= 1;
	} else {
		if (player.hp > hp) {
			int dmgToDeal = hp;
			player.TakeDamage(dmgToDeal);
			TakeDamage(dmgToDeal);
		} else {
			int dmgToDeal = player.hp;
			TakeDamage(dmgToDeal);
			player.TakeDamage(dmgToDeal);
		}
	}

	if (player.currentWeapon && player.currentWeapon->currentDurability <= 0) {
		player.currentWeapon.reset();
	}

	if (hp > 0) {
		return {.replace = false, .replaceInto = nullptr};
	}

	return {.replace = true,
			.replaceInto = std::make_shared<CoinCard>(startHp)};
}
