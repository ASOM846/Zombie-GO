#include "weaponCard.hpp"
#include "card.hpp"
#include "playerCard.hpp"

MeleWeaponCard::MeleWeaponCard() {
	struct WeaponParms {
		std::string name;
		TextureId texture;
	};

	auto GetRandomParms = [this]() {
		std::vector<WeaponParms> parms{
			{"WRENCH", TextureId::WEAPON_0},  {"AXE", TextureId::WEAPON_1},
			{"CROWBAR", TextureId::WEAPON_2}, {"MACHETE", TextureId::WEAPON_3},
			{"PAN", TextureId::WEAPON_4},	  {"SICKLE", TextureId::WEAPON_5},
			{"KNIFE", TextureId::WEAPON_6}};

		int seed = GetRandomValue(0, parms.size() - 1);

		return parms[seed];
	};

	WeaponParms parms = GetRandomParms();

	name = parms.name;
	textureId = parms.texture;

	attack = GetRandomValue(3, 8);
}

void MeleWeaponCard::RenderContent(Vector2 offset, Vector2 cellSize,
								   TextureManager &tm) {}

std::string MeleWeaponCard::GetValueText() const {
	return std::to_string(attack);
}

InteractionResult MeleWeaponCard::Interact(PlayerCard &player) {
	player.currentWeapon = std::make_shared<MeleWeaponCard>(*this);

	return {.replace = true, .replaceInto = nullptr};
}
