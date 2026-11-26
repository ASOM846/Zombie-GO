#pragma once

#include "../../textureManager.hpp"

#include <memory>
#include <raylib.h>
#include <string>

class Spell;

class PlayerCard;
class SwordCard;
class Card;

enum class GameEvent {
	NONE,
	ADVANCE_ROOM
};

struct InteractionResult {
	bool replace;
	std::shared_ptr<Card> replaceInto;
	GameEvent event{GameEvent::NONE};
};

class Card {
  public:
	Card() = default;
	virtual ~Card() = default;

	virtual void Render(Vector2 offset, Vector2 cellSize, TextureManager &tm);

	[[nodiscard]] virtual std::string GetTopText() const = 0;
	[[nodiscard]] virtual std::string GetBottomText() const = 0;

  protected:
	virtual void RenderContent(Vector2 offset, Vector2 cellSize,
							   TextureManager &tm) = 0;

  public:
	virtual InteractionResult Interact(PlayerCard &player) = 0;
	virtual void AutoAction(PlayerCard &player) = 0;

	virtual void TakeDamage(int value);

	Vector2 renderPos{0, 0};
	Vector2 targetPos{0, 0};

	void SetTargetPos(Vector2 target);

	bool isAnimating{false};
	bool hasRenderPosition;

	void UpdateAnimation(float dt);

	float scale = 0.0F;
	bool isSpawning = true;

	int hp;

	std::string name;

	Color gradientColor{BLANK};
	TextureId textureId;

	bool isHighlited{false};
	Color highlightColor;
};
