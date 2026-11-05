#include "board.hpp"
#include "../entity/card/activeEnemyCard.hpp"
#include "../entity/card/chestCard.hpp"
#include "../entity/card/coinCard.hpp"
#include "../entity/card/enemyCard.hpp"
#include "../entity/card/healthPotionCard.hpp"
#include "../entity/card/playerCard.hpp"
#include "../entity/card/spellRecepieCard.hpp"
#include "../entity/card/trapCard.hpp"
#include "../entity/card/weaponCard.hpp"
#include "../entity/spell/spell.hpp"
#include "../graphics/gfx.hpp"
#include "../textureManager.hpp"

#include <functional>
#include <memory>
#include <raylib.h>

void Board::Init() {
	board.resize(boardY, std::vector<std::shared_ptr<Card>>(boardX));
	Reset();
}

void Board::Reset() {
	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			board[y][x] = GetRandomCard();
		}
	}

	board[1][1] = std::make_shared<PlayerCard>();
}

void Board::Update(ScreenShake &ss) {
	float dt = GetFrameTime();

	Vector2 cellSize = {static_cast<float>(cellWidth),
						static_cast<float>(cellHeight)};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			auto &card = board[y][x];

			Vector2 target{boardOffset.x + (cellWidth + spacing) * x,
						   boardOffset.y + (cellHeight + spacing) * y};

			card->SetTargetPos(target);
			card->UpdateAnimation(dt);
		}
	}
}

void Board::OnActionUpdate(ScreenShake &ss) {
	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			board[y][x]->AutoAction(*GetPlayer());
		}
	}
}

void Board::UpdateHighlights(std::shared_ptr<Spell> selectedSpell) {
	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			auto &card = board[y][x];
			if (card == nullptr) {
				continue;
			}

			if (selectedSpell != nullptr) {
				card->isHighlited = selectedSpell->ShouldHighlight(card);
			} else {
				card->isHighlited = false;
			}
		}
	}
}

void Board::Render(TextureManager &tm) {
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

			board[y][x]->Render(board[y][x]->renderPos, cellSize, tm);
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

	if (std::dynamic_pointer_cast<ChestCard>(target) != nullptr) {
		board[targetY][playerPos.x] = std::make_shared<CoinCard>();
		return;
	}

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

	if (std::dynamic_pointer_cast<ChestCard>(target) != nullptr) {
		board[targetY][playerPos.x] = std::make_shared<CoinCard>();
		return;
	}

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

	if (std::dynamic_pointer_cast<ChestCard>(target) != nullptr) {
		board[playerPos.y][targetX] = std::make_shared<CoinCard>();
		return;
	}

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

	if (std::dynamic_pointer_cast<ChestCard>(target) != nullptr) {
		board[playerPos.y][targetX] = std::make_shared<CoinCard>();
		return;
	}

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

std::shared_ptr<Card> Board::GetCellAtPosition(Vector2 posistion) {
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

			Rectangle rect{finalPos.x, finalPos.y, cellSize.x, cellSize.y};

			if (CheckCollisionPointRec(posistion, rect)) {
				return board[y][x];
			}
		}
	}

	return nullptr;
}

std::shared_ptr<Card> Board::GetRandomCard() {
	std::vector<std::pair<int, std::function<std::shared_ptr<Card>()>>>
		weightedPool = {
			{60, []() { return std::make_shared<EnemyCard>(); }},
			{15, []() { return std::make_shared<TrapCard>(); }},
			{10, []() { return std::make_shared<ActiveEnemyCard>(); }},
			{10, []() { return std::make_shared<HealthPotionCard>(); }},
			{10, []() { return std::make_shared<SpellRecepieCard>(); }},
			{10, []() { return std::make_shared<ChestCard>(); }},
			{10, []() { return std::make_shared<MeleWeaponCard>(); }}};

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

	return std::make_shared<EnemyCard>();
}

void Board::RecalculateDrawindVariables(int bottomButtonsHeight) {
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	int buttonBoardSpacing = 50 * gfx::userFontScale;

	minOffset.y = bottomButtonsHeight + buttonBoardSpacing;

	touchRec = {.x = minOffset.x,
				.y = minOffset.y,
				.width = static_cast<float>(screenWidth - minOffset.x * 2),
				.height = static_cast<float>(screenHeight - minOffset.y * 2)};

	int maxCellWidth =
		(static_cast<int>(touchRec.width) - (spacing * boardX + 1)) / boardX;
	int maxCellHeight;

	cellWidth = maxCellWidth;
	cellHeight = maxCellWidth * 1.333333f;

	if ((cellHeight * boardY + (boardY + 1) * spacing) >= touchRec.height) {
		maxCellHeight =
			(static_cast<int>(touchRec.height) - (spacing * boardY + 1)) /
			boardY;

		cellWidth = maxCellHeight * 0.755555f;
		cellHeight = maxCellHeight;
	}

	float totalBoardWidth = (cellWidth * boardX + spacing * (boardX - 1));
	float totalBoardHeight = (cellHeight * boardY + spacing * (boardY - 1));

	boardOffset = {.x = touchRec.x + (touchRec.width - totalBoardWidth) / 2.0f,
				   .y = touchRec.y +
						(touchRec.height - totalBoardHeight) / 2.0f};
}
