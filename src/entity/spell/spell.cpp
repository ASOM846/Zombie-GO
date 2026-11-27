#include "spell.hpp"
#include <memory>
#include <raylib.h>

#include "../../graphics/gfx.hpp"
#include "../card/activeEnemyCard.hpp"
#include "../card/card.hpp"
#include "../card/enemyCard.hpp"
#include "../card/playerCard.hpp"

void Pickable::Render(Vector2 position, Vector2 size, TextureManager &tm) {
	gfx::DrawPickable(*this, position, size, tm);
	RenderContent(position, size);
}

MedkidPickable::MedkidPickable() {
	healAmount = 5;
	name = "MEDKIT 5";
	highlightColor = {105, 130, 65, 180};
	textureId = TextureId::MEDKIT_0;
}

void MedkidPickable::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("MEDKIT 5", offset.x + 10, offset.y + 10, 20, RED);
}

bool MedkidPickable::Interact(std::shared_ptr<Card> target) {

	if (auto playerTarget = std::dynamic_pointer_cast<PlayerCard>(target)) {
		playerTarget->Heal(healAmount);
		return true;
	}

	return false;
}

bool MedkidPickable::ShouldHighlight(std::shared_ptr<Card> &target) {
	if (auto playerTarget = std::dynamic_pointer_cast<PlayerCard>(target)) {
		return true;
	}

	return false;
}

MolotowPickable::MolotowPickable() {
	damageAmount = 5;
	name = "MOLOTOW 5";
	highlightColor = {135, 65, 65, 180};
	textureId = TextureId::MOLOTOW_0;
}

void MolotowPickable::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("DAMAGE  5", offset.x + 10, offset.y + 10, 20, RED);
}

bool MolotowPickable::Interact(std::shared_ptr<Card> target) {
	if (auto enemyTarget = std::dynamic_pointer_cast<EnemyCard>(target)) {
		enemyTarget->TakeDamage(damageAmount);
		return true;
	}

	if (auto enemyTarget = std::dynamic_pointer_cast<ActiveEnemyCard>(target)) {
		enemyTarget->TakeDamage(damageAmount);
		return true;
	}

	return false;
}

bool MolotowPickable::ShouldHighlight(std::shared_ptr<Card> &target) {
	if (auto enemyTarget = std::dynamic_pointer_cast<EnemyCard>(target)) {
		return true;
	}

	if (auto enemyTarget = std::dynamic_pointer_cast<ActiveEnemyCard>(target)) {
		return true;
	}

	return false;
}
