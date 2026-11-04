#include "weaponCard.hpp"
#include "playerCard.hpp"

SwordCard::SwordCard() {
	struct WeaponParms {
		std::string name;
		TextureId texture;
	};

	auto GetRandomParms = [this]() {
		std::vector<WeaponParms> parms{{"SWORD", TextureId::WEAPON_0},
									   {"AXE", TextureId::WEAPON_1},
									   {"BATON", TextureId::WEAPON_2},
									   {"DOUBLE AXE", TextureId::WEAPON_3},
									   {"HAMMER", TextureId::WEAPON_4},
									   {"KNIFE", TextureId::WEAPON_5},
									   {"SAW SWORD", TextureId::WEAPON_6}};

		int seed = GetRandomValue(0, parms.size() - 1);

		return parms[seed];
	};

	WeaponParms parms = GetRandomParms();

	name = parms.name;
	textureId = parms.texture;

	attack = GetRandomValue(3, 8);
}

void SwordCard::RenderContent(Vector2 offset, Vector2 cellSize,
							  TextureManager &tm) {}

std::string SwordCard::GetValueText() const {
	return std::to_string(attack);
}

bool SwordCard::Interact(PlayerCard &player) {
	player.currentWeapon = std::make_shared<SwordCard>(*this);

	return true;
}
