#include "activeEnemyCard.hpp"
#include "card.hpp"
#include "coinCard.hpp"
#include "playerCard.hpp"
#include <raylib.h>

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

	turnsToAttack = GetRandomValue(2, 4);
	toAttackCounter = 0;
}

void ActiveEnemyCard::RenderContent(Vector2 offset, Vector2 cellSize,
									TextureManager &tm) {}

std::string ActiveEnemyCard::GetTopText() const {
	return {name};
}

std::string ActiveEnemyCard::GetBottomText() const {
	return std::to_string(hp);
}

[[nodiscard]] int ActiveEnemyCard::GetMaxCounterLength() const {
	return turnsToAttack;
}

[[nodiscard]] int ActiveEnemyCard::GetCurrentCounterLenght() const {
	return toAttackCounter;
}

InteractionResult ActiveEnemyCard::Interact(PlayerCard &player) {
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

	// std::cerr << "damage dealt::::  " << std::to_string(playerDmg) <<
	// std::endl;

	if (hp > 0) {
		return {.replace = false, .replaceInto = nullptr};
	}

	return {.replace = true,
			.replaceInto = std::make_shared<CoinCard>(startHp)};
}

InteractionResult ActiveEnemyCard::AutoAction(PlayerCard &player) {
	if (toAttackCounter >= turnsToAttack) {
		player.TakeDamage(1);
		toAttackCounter = 0;
	} else {
		toAttackCounter++;
	}

	if (hp <= 0) {
		return {
			.replace = true, .replaceInto = nullptr, .event = GameEvent::NONE};
	}

	return {.replace = true, .replaceInto = nullptr, .event = GameEvent::NONE};
}
