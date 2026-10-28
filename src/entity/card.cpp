#include "card.hpp"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

void Card::Render(Vector2 position, Vector2 cellSize) {
	float centerX = position.x + cellSize.x / 2.0f;
	float centerY = position.y + cellSize.y / 2.0f;

	int width = cellSize.x;
	int height = cellSize.y;

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

	// int fontSize = 20;
	// const char *name = topCard->name.c_str();
	// int textWidth = MeasureText(name, fontSize);
	// int texX = position.x + width / 2 - textWidth / 2;
	// DrawText(name, texX, position.y + 16, fontSize, {40, 20, 10, 255});
	//
	// const float sepY = position.y + 42;
	// DrawLineEx({position.x + 14, sepY}, {position.x + width - 14, sepY}, 2,
	// 		   goldAccent);
	// DrawCircle(position.x + 14, sepY, 2, darkWood);
	// DrawCircle(position.x + width - 14, sepY, 2, darkWood);
	//
	// const char *valueStr;
	// if (topCard->maxValue == -1 || topCard->minValue == -1) {
	// 	valueStr = TextFormat("%d", topCard->hp);
	// } else {
	// 	valueStr = TextFormat("%d | %d", topCard->minValue, topCard->maxValue);
	// }
	//
	// if (topCard->type == CardType::PLAYER) {
	// 	valueStr = TextFormat("%d | %d", topCard->hp, topCard->maxValue);
	// }
	//
	// const float sepYBottom = position.y + height - 46;
	// DrawLineEx({position.x + 14, sepYBottom},
	// 		   {position.x + width - 14, sepYBottom}, 2, goldAccent);
	// DrawCircle(position.x + 14, sepYBottom, 2, darkWood);
	// DrawCircle(position.x + width - 14, sepYBottom, 2, darkWood);
	//
	// fontSize = 24;
	// textWidth = MeasureText(valueStr, fontSize);
	// int valTextX = centerX - textWidth / 2;
	// int valTextY = sepYBottom + 8;
	//
	// auto valueColor = Color{50, 30, 20, 255};
	// if (topCard->type == CardType::ENEMY)
	// 	valueColor = Color{150, 25, 25, 255};
	// if (topCard->type == CardType::POTION)
	// 	valueColor = Color{25, 110, 25, 255};
	//
	// DrawText(valueStr, valTextX, valTextY, fontSize, valueColor);

	RenderContent(position, cellSize);
}

PlayerCard::PlayerCard() {
	attackPower = 5;
	maxHp = 100;

	hp = maxHp;
}

void PlayerCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	const char *value = std::to_string(hp).c_str();

	DrawText(value, offset.x + 30, offset.y + 20, 30, GREEN);

	const char *attackValue = std::to_string(attackPower).c_str();

	DrawText(attackValue, offset.x + 30, offset.y + 60, 30, RED);
}

bool PlayerCard::Interact(PlayerCard &player) {}

EnemyCard::EnemyCard() {
	hp = GetRandomValue(1, 6);

	auto GetRandomColor = []() {
		std::vector<Color> colors{RED,	  GREEN,  BLUE,	 MAGENTA,
								  PURPLE, YELLOW, ORANGE};

		int seed = GetRandomValue(0, colors.size() - 1);

		return colors[seed];
	};

	color = GetRandomColor();
}

void EnemyCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	const char *value = std::to_string(hp).c_str();

	DrawText(value, offset.x + 30, offset.y + 20, 30, WHITE);
}

bool EnemyCard::Interact(PlayerCard &player) {
	int playerDmg = 0;

	if (player.attackPower > 0) {
		playerDmg = player.attackPower;

		player.attackPower -= hp;
		hp -= playerDmg;

		if (player.attackPower < 0)
			player.attackPower = 0;

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
	attack = GetRandomValue(3, 10);
}

void SwordCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	DrawRectangleLines(offset.x, offset.y, cellSize.x, cellSize.y, YELLOW);

	const char *value = std::to_string(attack).c_str();

	DrawText(value, offset.x + 30, offset.y + 20, 30, WHITE);
}

bool SwordCard::Interact(PlayerCard &player) {
	player.attackPower = attack;

	return true;
}

HealthPotionCard::HealthPotionCard() {
	amount = GetRandomValue(3, 12);
}

void HealthPotionCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	DrawRectangleLines(offset.x, offset.y, cellSize.x, cellSize.y, GREEN);

	std::string title = "HP";
	DrawText(title.c_str(), offset.x + 30, offset.y + 20, 20, WHITE);

	const char *value = std::to_string(amount).c_str();

	DrawText(value, offset.x + 30, offset.y + 60, 30, WHITE);
}

bool HealthPotionCard::Interact(PlayerCard &player) {
	player.hp += amount;

	player.hp = std::min(player.hp, player.maxHp);

	return true;
}
