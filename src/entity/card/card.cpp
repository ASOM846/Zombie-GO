#include "card.hpp"
#include "../spell/spell.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

#include "../../graphics/gfx.hpp"

void Card::Render(Vector2 position, Vector2 cellSize, TextureManager &tm) {

	const float centerX = position.x + cellSize.x / 2.0f;
	const float centerY = position.y + cellSize.y / 2.0f;

	gfx::DrawCardBase(centerX, centerY, position, cellSize, tm, *this);

	auto transform = [&](float x, float y) -> Vector2 {
		return {centerX + (x - centerX) * scale,
				centerY + (y - centerY) * scale};
	};

	Vector2 contentPos = transform(position.x, position.y);
	RenderContent(contentPos, {cellSize.x * scale, cellSize.y * scale}, tm);
}

void Card::SetTargetPos(Vector2 target) {
	targetPos = target;

	if (isSpawning)
		renderPos = targetPos;

	if (!hasRenderPosition) {
		renderPos = target;
		hasRenderPosition = true;
	}

	float dx = target.x - renderPos.x;
	float dy = target.y - renderPos.y;

	isAnimating = dx * dx + dy * dy > 0.1f;
}

void Card::UpdateAnimation(float dt) {
	if (isSpawning) {
		scale += 4.0f * dt;
		if (scale >= 1.0f) {
			scale = 1.0f;
			isSpawning = false;
		}
	}

	if (!isAnimating)
		return;

	float speed = 12.0f;
	float t = 1.0f - expf(-speed * dt);

	renderPos.x += (targetPos.x - renderPos.x) * t;
	renderPos.y += (targetPos.y - renderPos.y) * t;

	float distanceX = targetPos.x - renderPos.x;
	float distanceY = targetPos.y - renderPos.y;

	if (distanceX * distanceX + distanceY * distanceY < 0.5f) {
		renderPos = targetPos;
		isAnimating = false;
	}
}

PlayerCard::PlayerCard() {
	name = "PLAYER";

	currentWeapon = std::make_shared<SwordCard>();
	currentWeapon->name = "SWORD";
	currentWeapon->attack = 5;

	maxHp = 12;

	hp = maxHp;
	coins = 0;

	textureId = TextureId::KNIGHT;
}

void PlayerCard::RenderContent(Vector2 offset, Vector2 cellSize,
							   TextureManager &tm) {

	if (currentWeapon) {
		float centerX = offset.x + cellSize.x / 2.0f;
		float centerY = offset.y + cellSize.y / 2.0f;

		const Texture2D &texture = tm.get(currentWeapon->textureId);

		float scale = 3.0F;

		float drawX = centerX - (texture.width * scale) / 2.0f - cellSize.x / 4;
		float drawY = centerY - (texture.height * scale) / 2.0f;

		DrawTextureEx(texture, {drawX, drawY - 5 * scale}, 0.0f, scale,
					  RAYWHITE);
	}
}

std::string PlayerCard::GetValueText() const {
	if (currentWeapon)
		return std::string{std::to_string(hp) + "/" + std::to_string(maxHp) +
						   "  |  " + std::to_string(currentWeapon->attack)};

	return std::string{std::to_string(hp) + "/" + std::to_string(maxHp)};
}

bool PlayerCard::Interact(PlayerCard &player) {}

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

bool EnemyCard::Interact(PlayerCard &player) {
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
		return false;
	}

	return true;
}

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

bool ActiveEnemyCard::Interact(PlayerCard &player) {
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
		return false;
	}

	return true;
}

void ActiveEnemyCard::AutoAction(PlayerCard &player) {
	hp += 1;
	if (GetRandomValue(1, 2) == 1)
		player.hp -= 1;
}

SwordCard::SwordCard() {
	struct WeaponParms {
		std::string name;
		TextureId texture;
	};

	auto GetRandomParms = [this]() {
		std::vector<WeaponParms> parms{{"SWORD", TextureId::WEAPON_0},
									   {"AXE", TextureId::WEAPON_1},
									   {"BATON", TextureId::WEAPON_2},
									   {"DOUBLE AXE", TextureId::WEAPON_3},
									   {"HAMMER", TextureId::WEAPON_4},
									   {"KNIFE", TextureId::WEAPON_5},
									   {"SAW SWORD", TextureId::WEAPON_6}};

		int seed = GetRandomValue(0, parms.size() - 1);

		return parms[seed];
	};

	WeaponParms parms = GetRandomParms();

	name = parms.name;
	textureId = parms.texture;

	attack = GetRandomValue(3, 8);
}

void SwordCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string SwordCard::GetValueText() const {
	return std::to_string(attack);
}

bool SwordCard::Interact(PlayerCard &player) {
	player.currentWeapon = std::make_shared<SwordCard>(*this);

	return true;
}

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

TrapCard::TrapCard() {
	name = "TRAP";
	attack = GetRandomValue(1, 8);
	textureId = TextureId::TRAP_0;
}

void TrapCard::RenderContent(Vector2 offset, Vector2 cellSize,
							 TextureManager &tm) {}

std::string TrapCard::GetValueText() const {
	return std::to_string(attack);
}

bool TrapCard::Interact(PlayerCard &player) {
	player.hp -= attack;
	return true;
}

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

ChestCard::ChestCard() {
	name = "CHEST";
	textureId = TextureId::CHEST_0;
}

void ChestCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string ChestCard::GetValueText() const {
	return "";
}

bool ChestCard::Interact(PlayerCard &player) {
	return false;
}

SpellRecepieCard::SpellRecepieCard() {
	name = "SPELL";

	auto GetRandomSpell = []() {
		std::vector<std::pair<int, std::function<std::shared_ptr<Spell>()>>>
			weightedPool = {
				{60, []() { return std::make_shared<HealSpell>(); }},
				{10, []() { return std::make_shared<DamageSpell>(); }}};

		int totalWeight = 0;
		for (const auto &entry : weightedPool) {
			totalWeight += entry.first;
		}

		int roll = GetRandomValue(0, totalWeight - 1);

		int currentSum = 0;
		for (const auto &entry : weightedPool) {
			currentSum += entry.first;
			if (roll < currentSum) {
				return entry.second();
			}
		}
	};

	spell = GetRandomSpell();

	textureId = TextureId::CRATE_0;
}

void SpellRecepieCard::RenderContent(Vector2 offset, Vector2 cellSize,
									 TextureManager &tm) {}

std::string SpellRecepieCard::GetValueText() const {
	return spell->name;
}

bool SpellRecepieCard::Interact(PlayerCard &player) {
	player.spells.push_back(spell);
	return true;
}
