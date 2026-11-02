#include "card.hpp"
#include "spell/spell.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

void Card::Render(Vector2 position, Vector2 cellSize, TextureManager &tm) {
	const float s = scale;

	const float centerX = position.x + cellSize.x / 2.0f;
	const float centerY = position.y + cellSize.y / 2.0f;

	auto transform = [&](float x, float y) -> Vector2 {
		return {centerX + (x - centerX) * s, centerY + (y - centerY) * s};
	};

	auto drawRect = [&](float x, float y, float w, float h, Color color) {
		Vector2 p = transform(x, y);

		DrawRectangle(static_cast<int>(p.x), static_cast<int>(p.y),
					  static_cast<int>(w * s), static_cast<int>(h * s), color);
	};

	auto drawLine = [&](Vector2 start, Vector2 end, float thickness,
						Color color) {
		Vector2 a = transform(start.x, start.y);
		Vector2 b = transform(end.x, end.y);

		DrawLineEx(a, b, thickness * s, color);
	};

	auto drawCircle = [&](float x, float y, float radius, Color color) {
		Vector2 p = transform(x, y);
		DrawCircleV(p, radius * s, color);
	};

	const auto shadow = Color{0, 0, 0, 100};
	const auto darkWood = Color{60, 30, 15, 255};
	const auto parchment = Color{220, 200, 170, 255};
	const auto goldAccent = Color{180, 130, 40, 255};

	const float width = cellSize.x;
	const float height = cellSize.y;

	drawRect(position.x + 4, position.y + 4, width, height, shadow);
	drawRect(position.x, position.y, width, height, darkWood);

	const float border = 6;

	drawRect(position.x + border, position.y + border, width - 2 * border,
			 height - 2 * border, parchment);

	const float innerMargin = border + 4;

	DrawRectangleLinesEx(
		{transform(position.x + innerMargin, position.y + innerMargin).x,
		 transform(position.x + innerMargin, position.y + innerMargin).y,
		 (width - 2 * innerMargin) * s, (height - 2 * innerMargin) * s},
		2 * s, goldAccent);

	const float cornerLen = 16.0f;
	const float thick = 4.0f;
	const float p = innerMargin;

	Vector2 tl = {position.x + p, position.y + p};
	Vector2 tr = {position.x + width - p, position.y + p};
	Vector2 bl = {position.x + p, position.y + height - p};
	Vector2 br = {position.x + width - p, position.y + height - p};

	drawLine(tl, {tl.x + cornerLen, tl.y}, thick, goldAccent);
	drawLine(tl, {tl.x, tl.y + cornerLen}, thick, goldAccent);

	drawLine(tr, {tr.x - cornerLen, tr.y}, thick, goldAccent);
	drawLine(tr, {tr.x, tr.y + cornerLen}, thick, goldAccent);

	drawLine(bl, {bl.x + cornerLen, bl.y}, thick, goldAccent);
	drawLine(bl, {bl.x, bl.y - cornerLen}, thick, goldAccent);

	drawLine(br, {br.x - cornerLen, br.y}, thick, goldAccent);
	drawLine(br, {br.x, br.y - cornerLen}, thick, goldAccent);

	const float niteRadius = 3;

	drawCircle(tl.x, tl.y, niteRadius, darkWood);
	drawCircle(tr.x, tr.y, niteRadius, darkWood);
	drawCircle(bl.x, bl.y, niteRadius, darkWood);
	drawCircle(br.x, br.y, niteRadius, darkWood);

	const int fontSize = 20;
	const char *text = name.c_str();

	const int textWidth = MeasureText(text, fontSize);

	Vector2 namePos = transform(centerX - textWidth / 2.0f, position.y + 16);

	DrawText(text, static_cast<int>(namePos.x), static_cast<int>(namePos.y),
			 std::max(1, static_cast<int>(fontSize * s)), {40, 20, 10, 255});

	const float sepY = position.y + 42;

	drawLine({position.x + 14, sepY}, {position.x + width - 14, sepY}, 2,
			 goldAccent);

	drawCircle(position.x + 14, sepY, 2, darkWood);
	drawCircle(position.x + width - 14, sepY, 2, darkWood);

	const float sepYBottom = position.y + height - 46;

	drawLine({position.x + 14, sepYBottom},
			 {position.x + width - 14, sepYBottom}, 2, goldAccent);

	drawCircle(position.x + 14, sepYBottom, 2, darkWood);
	drawCircle(position.x + width - 14, sepYBottom, 2, darkWood);

	std::string valueStr = GetValueText();

	const int valueFontSize = 24;
	const int valueWidth = MeasureText(valueStr.c_str(), valueFontSize);

	Vector2 valuePos = transform(centerX - valueWidth / 2.0f, sepYBottom + 8);

	DrawText(valueStr.c_str(), static_cast<int>(valuePos.x),
			 static_cast<int>(valuePos.y),
			 std::max(1, static_cast<int>(valueFontSize * s)),
			 {50, 30, 20, 255});

	const Texture2D &texture = tm.get(textureId);

	const float textureScale = 3.0f;

	float drawX = centerX - (texture.width * textureScale) / 2.0f;
	float drawY = centerY - (texture.height * textureScale) / 2.0f;

	Vector2 texturePos = transform(drawX, drawY - 5 * textureScale);

	DrawTextureEx(texture, texturePos, 0.0f, textureScale * s, RAYWHITE);

	Vector2 contentPos = transform(position.x, position.y);

	RenderContent(contentPos, {cellSize.x * s, cellSize.y * s}, tm);
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
	currentWeapon->attack = 10;

	maxHp = 12;

	hp = maxHp;
	coins = 0;

	textureId = TextureId::KNIGHT;
}

void PlayerCard::RenderContent(Vector2 offset, Vector2 cellSize,
							   TextureManager &tm) {

	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// int width = cellSize.x;
	// int height = cellSize.y;
	//
	const Texture2D &texture = tm.get(currentWeapon->textureId);

	float scale = 3.0F;

	float drawX = centerX - (texture.width * scale) / 2.0f - cellSize.x / 4;
	float drawY = centerY - (texture.height * scale) / 2.0f;

	DrawTextureEx(texture, {drawX, drawY - 5 * scale}, 0.0f, scale, RAYWHITE);
}

std::string PlayerCard::GetValueText() const {
	return std::string{std::to_string(hp) + "/" + std::to_string(maxHp) +
					   "  |  " + std::to_string(currentWeapon->attack)};
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

		if (player.currentWeapon->attack < 0)
			player.currentWeapon->attack = 0;

	} else {
		playerDmg = player.hp;

		player.hp -= hp;
		hp -= playerDmg;

		if (player.hp < 0)
			player.hp = 0;
	}

	std::cout << "ENEMY ATTACKED" << std::endl;

	if (hp > 0) {
		return false;
	}

	return true;
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
	textureId = TextureId::ENEMY_0;
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
