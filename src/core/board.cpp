#include "board.hpp"
#include "../entity/card/activeEnemyCard.hpp"
#include "../entity/card/chestCard.hpp"
#include "../entity/card/coinCard.hpp"
#include "../entity/card/enemyCard.hpp"
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
#include <raymath.h>

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

	Vector2 cellSize = {static_cast<float>(gfx::cellWidth),
						static_cast<float>(gfx::cellHeight)};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			auto &card = board[y][x];

			Vector2 target{boardOffset.x + (gfx::cellWidth + spacing) * x,
						   boardOffset.y + (gfx::cellHeight + spacing) * y};

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

void Board::UpdateHighlights(std::shared_ptr<Pickable> selectedPickable) {
	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			auto &card = board[y][x];
			if (card == nullptr) {
				continue;
			}

			if (selectedPickable != nullptr) {
				card->isHighlited = selectedPickable->ShouldHighlight(card);
				card->highlightColor = selectedPickable->highlightColor;
			} else {
				card->isHighlited = false;
				card->highlightColor = BLANK;
			}
		}
	}
}

void Board::Render(TextureManager &tm) {
	Vector2 offset{
		static_cast<float>((GetScreenWidth() - (gfx::cellWidth * boardX +
												spacing * (boardX - 1))) /
						   2),
		static_cast<float>((GetScreenHeight() - (gfx::cellHeight * boardY +
												 spacing * (boardY - 1))) /
						   2)};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			Vector2 finalPos = {offset.x + ((gfx::cellWidth + spacing) * x),
								offset.y + ((gfx::cellHeight + spacing) * y)};

			Vector2 cellSize = {static_cast<float>(gfx::cellWidth),
								static_cast<float>(gfx::cellHeight)};

			board[y][x]->Render(board[y][x]->renderPos, cellSize, tm);
		}
	}
}

void Board::HandleSwipe(Vector2 direction) {
	Vector2 playerPos = GetPlayerPos();
	Vector2 desiredPos = Vector2Add(playerPos, direction);

	if (desiredPos.x < 0 || desiredPos.y < 0 || desiredPos.y > boardY ||
		desiredPos.x > boardX) {
		return;
	}

	auto player =
		std::dynamic_pointer_cast<PlayerCard>(board[playerPos.y][playerPos.x]);

	auto target = board[desiredPos.y][desiredPos.x];

	if (std::dynamic_pointer_cast<ChestCard>(target) != nullptr) {
		board[desiredPos.y][desiredPos.x] = std::make_shared<CoinCard>();
		return;
	}

	if (target != nullptr) {
		InteractionResult result = target->Interact(*player);

		// true i nullptr - usunięcie
		// false i nullptr - brak reakcji
		// false i ptr - zamiana w zapisana

		if ((result.replace == false) && (result.replaceInto == nullptr)) {
			return;
		}

		if ((result.replace == true) && (result.replaceInto != nullptr)) {
			board[desiredPos.y][desiredPos.x] = result.replaceInto;
			return;
		}
	}

	board[desiredPos.y][desiredPos.x] = board[playerPos.y][playerPos.x];

	if (direction.y == 1) {
		for (int y = playerPos.y; y > 0; y--) {
			board[y][playerPos.x] = board[y - 1][playerPos.x];
		}

		board[0][playerPos.x] = GetRandomCard();
	} else if (direction.y == -1) {
		for (int y = playerPos.y; y < boardY - 1; y++) {
			board[y][playerPos.x] = board[y + 1][playerPos.x];
		}

		board[boardY - 1][playerPos.x] = GetRandomCard();
	} else if (direction.x == 1) {
		for (int x = playerPos.x; x > 0; x--) {
			board[playerPos.y][x] = board[playerPos.y][x - 1];
		}

		board[playerPos.y][0] = GetRandomCard();
	} else {
		for (int x = playerPos.x; x < boardX - 1; x++) {
			board[playerPos.y][x] = board[playerPos.y][x + 1];
		}

		board[playerPos.y][boardX - 1] = GetRandomCard();
	}
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
		static_cast<float>((GetScreenWidth() - (gfx::cellWidth * boardX +
												spacing * (boardX - 1))) /
						   2),
		static_cast<float>((GetScreenHeight() - (gfx::cellHeight * boardY +
												 spacing * (boardY - 1))) /
						   2)};

	for (int y = 0; y < boardY; y++) {
		for (int x = 0; x < boardX; x++) {
			Vector2 finalPos = {offset.x + ((gfx::cellWidth + spacing) * x),
								offset.y + ((gfx::cellHeight + spacing) * y)};

			Vector2 cellSize = {static_cast<float>(gfx::cellWidth),
								static_cast<float>(gfx::cellHeight)};

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
			{10, []() { return std::make_shared<TrapCard>(); }},
			{10, []() { return std::make_shared<ActiveEnemyCard>(); }},
			{15, []() { return std::make_shared<SpellRecepieCard>(); }},
			{10, []() { return std::make_shared<ChestCard>(); }},
			{15, []() { return std::make_shared<MeleWeaponCard>(); }}};

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

	gfx::cellWidth = maxCellWidth;
	gfx::cellHeight = maxCellWidth * 1.333333f;

	if ((gfx::cellHeight * boardY + (boardY + 1) * spacing) >=
		touchRec.height) {
		maxCellHeight =
			(static_cast<int>(touchRec.height) - (spacing * boardY + 1)) /
			boardY;

		gfx::cellWidth = maxCellHeight * 0.755555f;
		gfx::cellHeight = maxCellHeight;
	}

	float totalBoardWidth = (gfx::cellWidth * boardX + spacing * (boardX - 1));
	float totalBoardHeight =
		(gfx::cellHeight * boardY + spacing * (boardY - 1));

	boardOffset = {.x = touchRec.x + (touchRec.width - totalBoardWidth) / 2.0f,
				   .y = touchRec.y +
						(touchRec.height - totalBoardHeight) / 2.0f};
}
