#include "spellRecepieCard.hpp"
#include "../spell/spell.hpp"
#include "card.hpp"
#include "playerCard.hpp"

#include <functional>
#include <vector>

SpellRecepieCard::SpellRecepieCard() {
	name = "SPELL";

	auto GetRandomSpell = []() {
		std::vector<std::pair<int, std::function<std::shared_ptr<Pickable>()>>>
			weightedPool = {
				{10, []() { return std::make_shared<MedkidPickable>(); }},
				{10, []() { return std::make_shared<MolotowPickable>(); }}};

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

	pickable = GetRandomSpell();

	textureId = pickable->textureId;
}

void SpellRecepieCard::RenderContent(Vector2 offset, Vector2 cellSize,
									 TextureManager &tm) {}

std::string SpellRecepieCard::GetValueText() const {
	return pickable->name;
}

InteractionResult SpellRecepieCard::Interact(PlayerCard &player) {
	player.pickables.push_back(pickable);

	return {.replace = true, .replaceInto = nullptr};
}
