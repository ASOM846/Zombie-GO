#pragma once

#include <raylib.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

enum class TextureId {
	KNIGHT,

	BCG_0,

	VIGNETTE_0,

	TRAP_0,

	MOLOTOW_0,

	MEDKIT_0,

	CRATE_0,

	COIN_0,

	FLASK_0,
	FLASK_1,
	FLASK_2,

	WEAPON_0,
	WEAPON_1,
	WEAPON_2,
	WEAPON_3,
	WEAPON_4,
	WEAPON_5,
	WEAPON_6,

	ACTIVE_ENEMY_0,

	ENEMY_0,
	ENEMY_1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_5,
};

class TextureManager {
  public:
	TextureManager() = default;
	~TextureManager() { unloadAll(); };

	const Texture2D &get(TextureId id) const {
		auto it = textures.find(id);
		if (it == textures.end()) {
			throw std::runtime_error("No texture was found");
		}
		return it->second;
	}

	void loadAll() {

		load(TextureId::KNIGHT, "assets/knight.png");

		load(TextureId::BCG_0, "assets/bcg0.png");

		load(TextureId::VIGNETTE_0, "assets/vignette0.png");

		load(TextureId::TRAP_0, "assets/trap0.png");

		load(TextureId::MOLOTOW_0, "assets/molotow0.png");

		load(TextureId::MEDKIT_0, "assets/medkit0.png");

		load(TextureId::CRATE_0, "assets/crate0.png");

		load(TextureId::COIN_0, "assets/coin0.png");

		load(TextureId::FLASK_0, "assets/flask0.png");
		load(TextureId::FLASK_1, "assets/flask1.png");
		load(TextureId::FLASK_2, "assets/flask2.png");

		load(TextureId::WEAPON_0, "assets/weapon0.png");
		load(TextureId::WEAPON_1, "assets/weapon1.png");
		load(TextureId::WEAPON_2, "assets/weapon2.png");
		load(TextureId::WEAPON_3, "assets/weapon3.png");
		load(TextureId::WEAPON_4, "assets/weapon4.png");
		load(TextureId::WEAPON_5, "assets/weapon5.png");
		load(TextureId::WEAPON_6, "assets/weapon6.png");

		load(TextureId::ACTIVE_ENEMY_0, "assets/mage0.png");

		load(TextureId::ENEMY_0, "assets/enemy0.png");
		load(TextureId::ENEMY_1, "assets/enemy1.png");
		load(TextureId::ENEMY_2, "assets/enemy2.png");
		load(TextureId::ENEMY_3, "assets/enemy3.png");
		load(TextureId::ENEMY_4, "assets/enemy4.png");
		load(TextureId::ENEMY_5, "assets/enemy5.png");
	}

	void load(TextureId id, const char *path) {
		TraceLog(LOG_INFO, "[TEXTURE] Loading: %s", path);

		TraceLog(LOG_INFO, "Working directory: %s", GetWorkingDirectory());
		TraceLog(LOG_INFO, "Asset exists: %s", FileExists(path) ? "YES" : "NO");

		Texture2D tex = LoadTexture(path);

		if (tex.id == 0) {
			TraceLog(LOG_ERROR, "[TEXTURE] FAILED: %s", path);

			throw std::runtime_error(std::string("Unable to load: ") + path);
		}

		TraceLog(LOG_INFO, "[TEXTURE] SUCCESS: %s", path);

		textures.emplace(id, tex);
	}

	void unloadAll() {
		for (auto &pair : textures) {
			UnloadTexture(pair.second);
		}
		textures.clear();
	}

	std::unordered_map<TextureId, Texture2D> textures;
};
