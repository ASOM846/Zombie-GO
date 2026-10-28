#include "board.hpp"
#include "cmath"
#include <memory>
#include <raylib.h>
#include <string>

void Board::Init() {
	board.resize(boardY, std::vector<std::shared_ptr<Card>>(boardX));

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			board[y][x] = std::make_shared<EnemyCard>();
		}
	}

	board[2][2] = std::make_shared<PlayerCard>();
}

void Board::Update() {}

void Board::Render() {
	Vector2 offset{
		static_cast<float>(
			(GetScreenWidth() - (cellWidth * boardX + spacing * (boardX - 1))) /
			2),
		static_cast<float>((GetScreenHeight() -
							(cellHeight * boardY + spacing * (boardY - 1))) /
						   2)};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			Vector2 finalPos = {offset.x + ((cellWidth + spacing) * x),
								offset.y + ((cellHeight + spacing) * y)};

			Vector2 cellSize = {static_cast<float>(cellWidth),
								static_cast<float>(cellHeight)};

			board[y][x]->Render(finalPos, cellSize);
		}
	}
}

void Board::HandleSwipeDown() {
	Vector2 playerPos = GetPlayerPos();

	if (playerPos.y == boardY - 1) {
		return;
	}

	int targetY = playerPos.y + 1;

	auto player =
		std::dynamic_pointer_cast<PlayerCard>(board[playerPos.y][playerPos.x]);

	auto target = board[targetY][playerPos.x];

	if (target != nullptr) {
		if (!target->Interact(*player)) {
			return;
		}
	}

	board[targetY][playerPos.x] = board[playerPos.y][playerPos.x];

	for (int y = playerPos.y; y > 0; y--) {
		board[y][playerPos.x] = board[y - 1][playerPos.x];
	}

	board[0][playerPos.x] = GetRandomCard();
}

void Board::HandleSwipeUp() {
	Vector2 playerPos = GetPlayerPos();

	if (playerPos.y == 0) {
		return;
	}

	int targetY = playerPos.y - 1;

	auto player =
		std::dynamic_pointer_cast<PlayerCard>(board[playerPos.y][playerPos.x]);

	auto target = board[targetY][playerPos.x];

	if (target != nullptr) {
		if (!target->Interact(*player)) {
			return;
		}
	}

	board[targetY][playerPos.x] = board[playerPos.y][playerPos.x];

	for (int y = playerPos.y; y < boardY - 1; y++) {
		board[y][playerPos.x] = board[y + 1][playerPos.x];
	}

	board[boardY - 1][playerPos.x] = GetRandomCard();
}

void Board::HandleSwipeLeft() {
	Vector2 playerPos = GetPlayerPos();

	if (playerPos.x == 0) {
		return;
	}

	int targetX = playerPos.x - 1;

	auto player =
		std::dynamic_pointer_cast<PlayerCard>(board[playerPos.y][playerPos.x]);

	auto target = board[playerPos.y][targetX];

	auto enemy = std::dynamic_pointer_cast<EnemyCard>(target);

	if (target != nullptr) {
		if (!target->Interact(*player)) {
			return;
		}
	}

	board[playerPos.y][targetX] = board[playerPos.y][playerPos.x];

	for (int x = playerPos.x; x < boardX - 1; x++) {
		board[playerPos.y][x] = board[playerPos.y][x + 1];
	}

	board[playerPos.y][boardX - 1] = GetRandomCard();
}

void Board::HandleSwipeRight() {
	Vector2 playerPos = GetPlayerPos();

	if (playerPos.x == boardX - 1) {
		return;
	}

	int targetX = playerPos.x + 1;

	auto player =
		std::dynamic_pointer_cast<PlayerCard>(board[playerPos.y][playerPos.x]);

	auto target = board[playerPos.y][targetX];

	if (target != nullptr) {
		if (!target->Interact(*player)) {
			return;
		}
	}

	board[playerPos.y][targetX] = board[playerPos.y][playerPos.x];

	for (int x = playerPos.x; x > 0; x--) {
		board[playerPos.y][x] = board[playerPos.y][x - 1];
	}

	board[playerPos.y][0] = GetRandomCard();
}

std::shared_ptr<PlayerCard> Board::GetPlayer() {
	Vector2 pos = GetPlayerPos();
	return std::dynamic_pointer_cast<PlayerCard>(board[pos.y][pos.x]);
}

Vector2 Board::GetPlayerPos() {
	Vector2 playerPos{-1, -1};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			if (std::dynamic_pointer_cast<PlayerCard>(board[y][x]) != nullptr) {
				playerPos.y = y;
				playerPos.x = x;
				break;
			}
		}
		if (playerPos.y != -1) {
			break;
		}
	}

	return playerPos;
}

std::shared_ptr<Card> Board::GetRandomCard() {
	int seed = GetRandomValue(0, 10);

	if (seed >= 7) {
		return std::make_shared<SwordCard>();
	}

	return std::make_shared<EnemyCard>();
}
