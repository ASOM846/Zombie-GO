#include "board.hpp"
#include "cmath"
#include <raylib.h>
#include <string>

void Board::Init() {
	board.resize(boardY, std::vector<int>(boardX));

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			board[y][x] = GetRandomValue(-3, 5);
		}
	}

	// 99 - temporaty player
	int centerY =
		static_cast<int>(std::ceil(static_cast<double>(boardY - 1) / 2.0));
	int centerX =
		static_cast<int>(std::ceil(static_cast<double>(boardX - 1) / 2.0));

	board[centerY][centerX] = 99;
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

			DrawRectangle(finalPos.x, finalPos.y, cellWidth, cellHeight, RED);

			const char *value = std::to_string(board[y][x]).c_str();

			DrawText(value, finalPos.x + 30, finalPos.y + 20, 30, WHITE);
		}
	}
}
