#pragma once

#include <memory>
#include <raylib.h>
#include <vector>

#include "../entity/card/card.hpp"
#include "../entity/card/playerCard.hpp"
#include "../graphics/screenShake.hpp"
#include "../textureManager.hpp"

struct BoardActionResult {
	bool turnConsumed{false};
	GameEvent event{GameEvent::NONE};
};

class Board {
  public:
	void Init();
	void Reset();

	void Update(ScreenShake &ss);
	void OnActionUpdate(ScreenShake &ss);
	void UpdateHighlights(std::shared_ptr<Pickable> selectedPickable);
	void Render(TextureManager &tm);

	BoardActionResult HandleSwipe(Vector2 direction);

	std::shared_ptr<PlayerCard> GetPlayer();

	std::shared_ptr<Card> GetCellAtPosition(Vector2 posistion);

	Rectangle const &GetTouchRec() { return touchRec; }
	int const &GetSpacing() { return spacing; }

	void RecalculateDrawindVariables(int bottomButtonsHeight);

  private:
	void RenderCell();

	Vector2 GetPlayerPos();

	std::shared_ptr<Card> GetRandomCard();

	std::vector<std::vector<std::shared_ptr<Card>>> board;

	Rectangle touchRec{};

	const int boardY = 3;
	const int boardX = 3;

	int maxCellWidth;

	const int spacing = 15;

	Vector2 minOffset{0, 100};
	Vector2 boardOffset{};
};
