#pragma once

#include <raylib.h>

class PlayerCard;

class Card {
  public:
	Card() = default;
	virtual ~Card() = default;

	virtual void Render(Vector2 offset, Vector2 cellSize) = 0;

	virtual bool Interact(PlayerCard &player) = 0;

	int hp;
};

class PlayerCard : public Card {
  public:
	PlayerCard();
	~PlayerCard() override = default;

	void Render(Vector2 offset, Vector2 cellSize) override;

	bool Interact(PlayerCard &player) override;

	int attackPower;
};

class EnemyCard : public Card {
  public:
	EnemyCard();
	~EnemyCard() override = default;

	void Render(Vector2 offset, Vector2 cellSize) override;

	bool Interact(PlayerCard &player) override;

	Color color;
};

class SwordCard : public Card {
  public:
	SwordCard();
	~SwordCard() override = default;

	void Render(Vector2 offset, Vector2 cellSize) override;

	bool Interact(PlayerCard &player) override;

	int attack;
};
