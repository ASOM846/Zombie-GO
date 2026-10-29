#pragma once

#include <raylib.h>
#include <string>

class PlayerCard;

class Card {
  public:
	Card() = default;
	virtual ~Card() = default;

	virtual void Render(Vector2 offset, Vector2 cellSize);

  protected:
	virtual void RenderContent(Vector2 offset, Vector2 cellSize) = 0;

	[[nodiscard]] virtual std::string GetValueText() const = 0;

  public:
	virtual bool Interact(PlayerCard &player) = 0;

	int hp;
	std::string name;
};

class PlayerCard : public Card {
  public:
	PlayerCard();
	~PlayerCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;

	int attackPower;
	int maxHp;
};

class EnemyCard : public Card {
  public:
	EnemyCard();
	~EnemyCard() override = default;

	void RenderContent(Vector2 position, Vector2 cellSize) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;

	Color color;
};

class SwordCard : public Card {
  public:
	SwordCard();
	~SwordCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;

	int attack;
};

class HealthPotionCard : public Card {
  public:
	HealthPotionCard();
	~HealthPotionCard() override = default;

	void RenderContent(Vector2 offset, Vector2 cellSize) override;

	[[nodiscard]] std::string GetValueText() const override;

	bool Interact(PlayerCard &player) override;

	int amount;
};
