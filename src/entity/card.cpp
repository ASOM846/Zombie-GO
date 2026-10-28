#include "card.hpp"
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>

PlayerCard::PlayerCard() {
	hp = 10;
	attackPower = 5;
}

void PlayerCard::Render(Vector2 offset, Vector2 cellSize) {
	DrawRectangle(offset.x, offset.y, cellSize.x, cellSize.y, WHITE);

	const char *value = std::to_string(hp).c_str();

	DrawText(value, offset.x + 30, offset.y + 20, 30, GREEN);

	const char *attackValue = std::to_string(attackPower).c_str();

	DrawText(attackValue, offset.x + 30, offset.y + 60, 30, RED);
}

bool PlayerCard::Interact(PlayerCard &player) {}

EnemyCard::EnemyCard() {
	hp = 0;
	while (hp == 0) {
		hp = GetRandomValue(-3, 6);
	}

	auto GetRandomColor = []() {
		std::vector<Color> colors{RED,	  GREEN,  BLUE,	 MAGENTA,
								  PURPLE, YELLOW, ORANGE};

		int seed = GetRandomValue(0, colors.size() - 1);

		return colors[seed];
	};

	color = GetRandomColor();
}

void EnemyCard::Render(Vector2 offset, Vector2 cellSize) {
	DrawRectangle(offset.x, offset.y, cellSize.x, cellSize.y, color);

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

void SwordCard::Render(Vector2 offset, Vector2 cellSize) {
	DrawRectangle(offset.x, offset.y, cellSize.x, cellSize.y, DARKGREEN);
	DrawRectangleLines(offset.x, offset.y, cellSize.x, cellSize.y, YELLOW);

	const char *value = std::to_string(attack).c_str();

	DrawText(value, offset.x + 30, offset.y + 20, 30, WHITE);
}

bool SwordCard::Interact(PlayerCard &player) {
	player.attackPower = attack;

	return true;
}
