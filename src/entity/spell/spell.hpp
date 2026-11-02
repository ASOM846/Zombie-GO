#pragma once

#include <memory>
#include <raylib.h>
#include <string>

class Card;

class Spell {
  public:
	Spell() = default;
	virtual ~Spell() = default;

	virtual void Render(Vector2 position, Vector2 size);

  protected:
	virtual void RenderContent(Vector2 offset, Vector2 size) = 0;

  public:
	virtual bool Interact(std::shared_ptr<Card> target) = 0;
	std::string name;

	int manaRequired;
};

class HealSpell : public Spell {
  public:
	HealSpell();
	~HealSpell() override = default;

	void RenderContent(Vector2 offset, Vector2 size) override;

	bool Interact(std::shared_ptr<Card> target) override;

	int healAmount;
};

class DamageSpell : public Spell {
  public:
	DamageSpell();
	~DamageSpell() override = default;

	void RenderContent(Vector2 offset, Vector2 size) override;

	bool Interact(std::shared_ptr<Card> target) override;

	int damageAmount;
};
