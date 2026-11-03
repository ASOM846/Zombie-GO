#pragma once

#include "../textureManager.hpp"
#include "spell/spell.hpp"

#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

class PlayerCard;
class SwordCard;

class Card {
  public:
	Card() = default;
	virtual ~Card() = default;

	virtual void Render(Vector2 offset, Vector2 cellSize, TextureManager &tm);

	[[nodiscard]] virtual std::string GetValueText() const = 0;

  protected:
	virtual void RenderContent(Vector2 offset, Vector2 cellSize,
							   TextureManager &tm) = 0;

  public:
	virtual bool Interact(PlayerCard &player) = 0;
	virtual void AutoAction(PlayerCard &player) = 0;

	Vector2 renderPos{0, 0};
	Vector2 targetPos{0, 0};

	void SetTargetPos(Vector2 target);

	bool isAnimating{false};
	bool hasRenderPosition;

	void UpdateAnimation(float dt);

	float scale = 0.0f;
	bool isSpawning = true;

	int hp;
	std::string name;

	TextureId textureId;
};

class PlayerCard : public Card {
  public:
	PlayerCard();
	~PlayerCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	std::shared_ptr<SwordCard> currentWeapon;

	std::vector<std::shared_ptr<Spell>> spells;

	int maxHp;

	int coins;
};

class EnemyCard : public Card {
  public:
	EnemyCard();
	~EnemyCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	Color color;
};

class ActiveEnemyCard : public Card {
  public:
	ActiveEnemyCard();
	~ActiveEnemyCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override;

	Color color;
};

class SwordCard : public Card {
  public:
	SwordCard();
	~SwordCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int attack;
};

class HealthPotionCard : public Card {
  public:
	HealthPotionCard();
	~HealthPotionCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int amount;
};

class TrapCard : public Card {
  public:
	TrapCard();
	~TrapCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int attack;
};

class CoinCard : public Card {
  public:
	CoinCard();
	~CoinCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	int value;
};

class ChestCard : public Card {
  public:
	ChestCard();
	~ChestCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};
};

class SpellRecepieCard : public Card {
  public:
	SpellRecepieCard();
	~SpellRecepieCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize,
					   TextureManager &tm) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;
	void AutoAction(PlayerCard &player) override {};

	std::shared_ptr<Spell> spell;
};
