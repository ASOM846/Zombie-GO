#include "spellRecepieCard.hpp"
#include "../spell/spell.hpp"
#include "playerCard.hpp"

#include <functional>
#include <vector>

SpellRecepieCard::SpellRecepieCard() {
	name = "SPELL";

	auto GetRandomSpell = []() {
		std::vector<std::pair<int, std::function<std::shared_ptr<Spell>()>>>
			weightedPool = {
				{60, []() { return std::make_shared<HealSpell>(); }},
				{10, []() { return std::make_shared<DamageSpell>(); }}};

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
	};

	spell = GetRandomSpell();

	textureId = TextureId::CRATE_0;
}

void SpellRecepieCard::RenderContent(Vector2 offset, Vector2 cellSize,
									 TextureManager &tm) {}

std::string SpellRecepieCard::GetValueText() const {
	return spell->name;
}

bool SpellRecepieCard::Interact(PlayerCard &player) {
	player.spells.push_back(spell);
	return true;
}
