#pragma once

#include <raylib.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

enum class TextureId {
	KNIGHT,

	TRAP_0,

	CHEST_0,

	FLASK_0,
	FLASK_1,
	FLASK_2,

	WEAPON_0,

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

		load(TextureId::TRAP_0, "assets/trap0.png");

		load(TextureId::CHEST_0, "assets/chest0.png");
		load(TextureId::FLASK_0, "assets/flask0.png");
		load(TextureId::FLASK_1, "assets/flask1.png");
		load(TextureId::FLASK_2, "assets/flask2.png");

		load(TextureId::WEAPON_0, "assets/weapon0.png");

		load(TextureId::ENEMY_0, "assets/enemy0.png");
		load(TextureId::ENEMY_1, "assets/enemy1.png");
		load(TextureId::ENEMY_2, "assets/enemy2.png");
		load(TextureId::ENEMY_3, "assets/enemy3.png");
		load(TextureId::ENEMY_4, "assets/enemy4.png");
		load(TextureId::ENEMY_5, "assets/enemy5.png");
	}

	void load(TextureId id, const char *path) {
		Texture2D tex = LoadTexture(path);
		if (tex.id == 0) {
			throw std::runtime_error(std::string("Unable to load: ") + path);
		}
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
