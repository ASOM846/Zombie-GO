#include "spell.hpp"
#include <raylib.h>

void Spell::Render(Vector2 offset, Vector2 size) {
	DrawRectangle(offset.x, offset.y, size.x, size.y, YELLOW);
	DrawRectangleLines(offset.x, offset.y, size.x, size.y, PINK);

	RenderContent(offset, size);
}

HealSpell::HealSpell() {
	healAmount = 5;
	name = "HEAL 5";
}

void HealSpell::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("HEAL  5", offset.x + 10, offset.y + 10, 20, RED);
}

void HealSpell::Interact(std::shared_ptr<Card> target) {
	target->hp += healAmount;
}

DamageSpell::DamageSpell() {
	damageAmount = 5;
	name = "DAMAGE 5";
}

void DamageSpell::RenderContent(Vector2 offset, Vector2 size) {
	DrawText("DAMAGE  5", offset.x + 10, offset.y + 10, 20, RED);
}

void DamageSpell::Interact(std::shared_ptr<Card> target) {
	target->hp -= damageAmount;
}
