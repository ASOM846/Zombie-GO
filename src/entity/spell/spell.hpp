#pragma once

#include <memory>
#include <raylib.h>
#include <string>

#include "../../textureManager.hpp"

class Card;

class Pickable {
  public:
	Pickable() = default;
	virtual ~Pickable() = default;

	virtual void Render(Vector2 position, Vector2 size);

  protected:
	virtual void RenderContent(Vector2 offset, Vector2 size) = 0;

  public:
	virtual bool Interact(std::shared_ptr<Card> target) = 0;
	virtual bool ShouldHighlight(std::shared_ptr<Card> &target) = 0;

	std::string name;

	Color highlightColor;
	TextureId textureId;
};

class MedkidPickable : public Pickable {
  public:
	MedkidPickable();
	~MedkidPickable() override = default;

	void RenderContent(Vector2 offset, Vector2 size) override;

	bool Interact(std::shared_ptr<Card> target) override;
	bool ShouldHighlight(std::shared_ptr<Card> &target) override;

	int healAmount;
};

class MolotowPickable : public Pickable {
  public:
	MolotowPickable();
	~MolotowPickable() override = default;

	void RenderContent(Vector2 offset, Vector2 size) override;

	bool Interact(std::shared_ptr<Card> target) override;
	bool ShouldHighlight(std::shared_ptr<Card> &target) override;

	int damageAmount;
};
