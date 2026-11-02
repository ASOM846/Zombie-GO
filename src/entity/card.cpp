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

	const char *valueStr = GetValueText().c_str();
	// if (topCard->maxValue == -1 || topCard->minValue == -1) {
	// 	valueStr = TextFormat("%d", topCard->hp);
	// } else {
	// 	valueStr = TextFormat("%d | %d", topCard->minValue, topCard->maxValue);
	// }
	//
	// if (topCard->type == CardType::PLAYER) {
	// 	valueStr = TextFormat("%d | %d", topCard->hp, topCard->maxValue);
	// }

	const float sepYBottom = position.y + height - 46;
	DrawLineEx({position.x + 14, sepYBottom},
			   {position.x + width - 14, sepYBottom}, 2, goldAccent);
	DrawCircle(position.x + 14, sepYBottom, 2, darkWood);
	DrawCircle(position.x + width - 14, sepYBottom, 2, darkWood);
	//
	fontSize = 24;
	textWidth = MeasureText(valueStr, fontSize);
	int valTextX = centerX - textWidth / 2;
	int valTextY = sepYBottom + 8;

	auto valueColor = Color{50, 30, 20, 255};
	// if (topCard->type == CardType::ENEMY)
	// 	valueColor = Color{150, 25, 25, 255};
	// if (topCard->type == CardType::POTION)
	// 	valueColor = Color{25, 110, 25, 255};

	DrawText(valueStr, valTextX, valTextY, fontSize, valueColor);

	RenderContent(position, cellSize);
}

PlayerCard::PlayerCard() {
	name = "PLAYER";

	currentWeapon = std::make_shared<SwordCard>();
	currentWeapon->name = "SWORD";
	currentWeapon->attack = 10;

	maxHp = 12;

	maxMana = 10;
	mana = maxMana;

	hp = maxHp;
	coins = 0;
}

void PlayerCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	// Rysujemy prostą ikonę gracza: sylwetkę hełmu/twarzy (koło + obrys)
	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// Miejsce na ikonę w środkowej części karty
	DrawCircle(centerX, centerY - 10, 18, Color{100, 120, 150, 255});
	DrawRectangle(centerX - 12, centerY + 8, 24, 20, Color{100, 120, 150, 255});

	// Mały napis informacyjny wewnątrz
	DrawText("HERO", centerX - MeasureText("HERO", 10) / 2, centerY + 32, 10,
			 DARKGRAY);
}

std::string PlayerCard::GetValueText() const {
	return std::string{std::to_string(hp) + "/" + std::to_string(maxHp) +
					   "  |  " + std::to_string(currentWeapon->attack)};
}

bool PlayerCard::Interact(PlayerCard &player) {}

EnemyCard::EnemyCard() {
	hp = GetRandomValue(1, 6);
	name = "ENEMY";

	auto GetRandomColor = []() {
		std::vector<Color> colors{RED,	  GREEN,  BLUE,	 MAGENTA,
								  PURPLE, YELLOW, ORANGE};

		int seed = GetRandomValue(0, colors.size() - 1);

		return colors[seed];
	};

	color = GetRandomColor();
}

void EnemyCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// Rysujemy stylizowaną "czaszkę" / mroczną sylwetkę wroga w losowym kolorze
	// karty
	DrawCircle(centerX, centerY - 5, 20, color);

	// Oczy wroga (wycięcia)
	DrawCircle(centerX - 7, centerY - 8, 4, RAYWHITE);
	DrawCircle(centerX + 7, centerY - 8, 4, RAYWHITE);

	// Usta/szczęka
	DrawRectangle(centerX - 5, centerY + 5, 10, 6, RAYWHITE);
}

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
	name = "WEAPON";
	attack = GetRandomValue(3, 10);
}

void SwordCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// Rysujemy prosty miecz skierowany w górę
	// Ostrze
	DrawRectangle(centerX - 3, centerY - 25, 6, 35, LIGHTGRAY);
	DrawTriangle({centerX - 3, centerY - 25}, {centerX + 3, centerY - 25},
				 {centerX, centerY - 35}, GRAY);
	// Jelec (crossguard)
	DrawRectangle(centerX - 12, centerY + 8, 24, 4, DARKGRAY);
	// Rękojeść i głowica
	DrawRectangle(centerX - 2, centerY + 12, 4, 12, BROWN);
	DrawCircle(centerX, centerY + 26, 4, GOLD);
}

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
}

void HealthPotionCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// Rysujemy buteleczkę mikstury z płynem
	// Szyjka butelki
	DrawRectangle(centerX - 4, centerY - 22, 8, 8, DARKGRAY);
	// Korek
	DrawRectangle(centerX - 6, centerY - 26, 12, 4, BROWN);
	// Korpus (bańka)
	DrawCircle(centerX, centerY + 4, 16, Fade(RED, 0.4f));
	DrawCircleLines(centerX, centerY + 4, 16, RED);

	// Biały refleks świetlny na miksturze
	DrawCircle(centerX - 5, centerY, 3, Fade(WHITE, 0.6f));
}

std::string HealthPotionCard::GetValueText() const {
	return std::to_string(amount);
}

bool HealthPotionCard::Interact(PlayerCard &player) {
	player.hp += amount;

	player.hp = std::min(player.hp, player.maxHp);

	return true;
}

ManaPotionCard::ManaPotionCard() {
	name = "MANA POTION";
	amount = GetRandomValue(3, 12);
}

void ManaPotionCard::RenderContent(Vector2 offset, Vector2 cellSize) {
	float centerX = offset.x + cellSize.x / 2.0f;
	float centerY = offset.y + cellSize.y / 2.0f;

	// Rysujemy buteleczkę mikstury z płynem
	// Szyjka butelki
	DrawRectangle(centerX - 4, centerY - 22, 8, 8, DARKGRAY);
	// Korek
	DrawRectangle(centerX - 6, centerY - 26, 12, 4, BROWN);
	// Korpus (bańka)
	DrawCircle(centerX, centerY + 4, 16, Fade(BLUE, 0.4f));
	DrawCircleLines(centerX, centerY + 4, 16, BLUE);

	// Biały refleks świetlny na miksturze
	DrawCircle(centerX - 5, centerY, 3, Fade(WHITE, 0.6f));
}

std::string ManaPotionCard::GetValueText() const {
	return std::to_string(amount);
}

bool ManaPotionCard::Interact(PlayerCard &player) {
	player.mana += amount;

	player.mana = std::min(player.mana, player.maxMana);

	return true;
}

TrapCard::TrapCard() {
	name = "TRAP";
	attack = GetRandomValue(1, 8);
}

void TrapCard::RenderContent(Vector2 offset, Vector2 cellSize) {}

std::string TrapCard::GetValueText() const {
	return std::to_string(attack);
}

bool TrapCard::Interact(PlayerCard &player) {
	player.hp -= attack;
	return true;
}
