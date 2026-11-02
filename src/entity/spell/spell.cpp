#include "spell.hpp"
#include <memory>
#include <raylib.h>

#include "../card.hpp"

void Spell::Render(Vector2 position, Vector2 size) {
	float centerX = position.x + size.x / 2.0f;
	float centerY = position.y + size.y / 2.0f;

	int width = size.x;
	int height = size.y;

	const auto shadow = Color{0, 0, 0, 100};
	const auto darkWood = Color{60, 30, 15, 255};
	const auto parchment = Color{220, 200, 170, 255};
	const auto goldAccent = Color{180, 130, 40, 255};

	DrawRectangle(position.x + 4, position.y + 4, width, height, shadow);
	DrawRectangle(position.x, position.y, width, height, darkWood);

	const float border = 6;
	float bgX = position.x + border;
	float bgY = position.y + border;
	float bgW = width - (2 * border);
	float bgH = height - (2 * border);

	DrawRectangle(position.x + border, position.y + border,
				  width - (2 * border), height - (2 * border), parchment);

	int innerMargin = border + 4;
	DrawRectangleLinesEx({position.x + static_cast<float>(innerMargin),
						  position.y + static_cast<float>(innerMargin),
						  static_cast<float>(width - (2 * innerMargin)),
						  static_cast<float>(height - (innerMargin * 2))},
						 2, goldAccent);

	float cornerLen = 16.0F;
	float thick = 4.0F;
	float p = innerMargin;

	Vector2 tl = {position.x + p, position.y + p};
	DrawLineEx(tl, {tl.x + cornerLen, tl.y}, thick, goldAccent);
	DrawLineEx(tl, {tl.x, tl.y + cornerLen}, thick, goldAccent);

	Vector2 tr = {position.x + width - p, position.y + p};
	DrawLineEx(tr, {tr.x - cornerLen, tr.y}, thick, goldAccent);
	DrawLineEx(tr, {tr.x, tr.y + cornerLen}, thick, goldAccent);

	Vector2 bl = {position.x + p, position.y + height - p};
	DrawLineEx(bl, {bl.x + cornerLen, bl.y}, thick, goldAccent);
	DrawLineEx(bl, {bl.x, bl.y - cornerLen}, thick, goldAccent);

	Vector2 br = {position.x + width - p, position.y + height - p};
	DrawLineEx(br, {br.x - cornerLen, br.y}, thick, goldAccent);
	DrawLineEx(br, {br.x, br.y - cornerLen}, thick, goldAccent);

	const float niteRadius = 3;
	DrawCircle(tl.x, tl.y, niteRadius, darkWood);
	DrawCircle(tr.x, tr.y, niteRadius, darkWood);
	DrawCircle(bl.x, bl.y, niteRadius, darkWood);
	DrawCircle(br.x, br.y, niteRadius, darkWood);

	int fontSize = 20;
	const char *text = name.c_str();
	int textWidth = MeasureText(text, fontSize);
	int texX = position.x + width / 2 - textWidth / 2;
	DrawText(text, texX, position.y + 16, fontSize, {40, 20, 10, 255});

	const float sepY = position.y + 42;
	DrawLineEx({position.x + 14, sepY}, {position.x + width - 14, sepY}, 2,
			   goldAccent);
	DrawCircle(position.x + 14, sepY, 2, darkWood);
	DrawCircle(position.x + width - 14, sepY, 2, darkWood);

	// const char *valueStr = GetValueText().c_str();
	//  if (topCard->maxValue == -1 || topCard->minValue == -1) {
	//  	valueStr = TextFormat("%d", topCard->hp);
	//  } else {
	//  	valueStr = TextFormat("%d | %d", topCard->minValue,
	//  topCard->maxValue);
	//  }
	//
	//  if (topCard->type == CardType::PLAYER) {
	//  	valueStr = TextFormat("%d | %d", topCard->hp, topCard->maxValue);
	//  }

	const float sepYBottom = position.y + height - 46;
	DrawLineEx({position.x + 14, sepYBottom},
			   {position.x + width - 14, sepYBottom}, 2, goldAccent);
	DrawCircle(position.x + 14, sepYBottom, 2, darkWood);
	DrawCircle(position.x + width - 14, sepYBottom, 2, darkWood);
	//
	// fontSize = 24;
	// textWidth = MeasureText(valueStr, fontSize);
	// int valTextX = centerX - textWidth / 2;
	// int valTextY = sepYBottom + 8;

	auto valueColor = Color{50, 30, 20, 255};
	// if (topCard->type == CardType::ENEMY)
	// 	valueColor = Color{150, 25, 25, 255};
	// if (topCard->type == CardType::POTION)
	// 	valueColor = Color{25, 110, 25, 255};

	// DrawText(valueStr, valTextX, valTextY, fontSize, valueColor);

	RenderContent(position, size);
}

HealSpell::HealSpell() {
	manaRequired = 5;

	healAmount = 5;
	name = "HEAL 5";
}

void HealSpell::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("HEAL  5", offset.x + 10, offset.y + 10, 20, RED);
}

bool HealSpell::Interact(std::shared_ptr<Card> target) {

	if (auto playerTarget = std::dynamic_pointer_cast<PlayerCard>(target)) {
		playerTarget->hp += healAmount;
		return true;
	}

	if (auto enemyTarget = std::dynamic_pointer_cast<EnemyCard>(target)) {
		enemyTarget->hp += healAmount;
		return true;
	}

	return false;
}

DamageSpell::DamageSpell() {
	manaRequired = 5;

	damageAmount = 5;
	name = "DAMAGE 5";
}

void DamageSpell::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("DAMAGE  5", offset.x + 10, offset.y + 10, 20, RED);
}

bool DamageSpell::Interact(std::shared_ptr<Card> target) {
	if (auto playerTarget = std::dynamic_pointer_cast<PlayerCard>(target)) {
		playerTarget->hp -= damageAmount;
		return true;
	}

	if (auto enemyTarget = std::dynamic_pointer_cast<EnemyCard>(target)) {
		enemyTarget->hp -= damageAmount;
		return true;
	}

	return false;
}
