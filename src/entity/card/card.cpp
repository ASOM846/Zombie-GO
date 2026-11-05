#include "card.hpp"
#include <algorithm>
#include <cmath>
#include <raylib.h>

#include "../../graphics/floatingText.hpp"
#include "../../graphics/gfx.hpp"

void Card::Render(Vector2 position, Vector2 cellSize, TextureManager &tm) {

	const float centerX = position.x + cellSize.x / 2.0f;
	const float centerY = position.y + cellSize.y / 2.0f;

	gfx::DrawCardBase(centerX, centerY, position, cellSize, tm, *this);

	auto transform = [&](float x, float y) -> Vector2 {
		return {centerX + (x - centerX) * scale,
				centerY + (y - centerY) * scale};
	};

	Vector2 contentPos = transform(position.x, position.y);
	RenderContent(contentPos, {cellSize.x * scale, cellSize.y * scale}, tm);
}

void Card::TakeDamage(int value) {
	hp -= value;
	hp = std::max(hp, 0);

	EffectManager::Get().SpawnText(
		{renderPos.x + gfx::cellWidth / 2, renderPos.y + gfx::cellHeight / 2},
		std::to_string(value).c_str(), RED);
}

void Card::SetTargetPos(Vector2 target) {
	targetPos = target;

	if (isSpawning)
		renderPos = targetPos;

	if (!hasRenderPosition) {
		renderPos = target;
		hasRenderPosition = true;
	}

	float dx = target.x - renderPos.x;
	float dy = target.y - renderPos.y;

	isAnimating = dx * dx + dy * dy > 0.1f;
}

void Card::UpdateAnimation(float dt) {
	if (isSpawning) {
		scale += 4.0f * dt;
		if (scale >= 1.0f) {
			scale = 1.0f;
			isSpawning = false;
		}
	}

	if (!isAnimating)
		return;

	float speed = 12.0f;
	float t = 1.0f - expf(-speed * dt);

	renderPos.x += (targetPos.x - renderPos.x) * t;
	renderPos.y += (targetPos.y - renderPos.y) * t;

	float distanceX = targetPos.x - renderPos.x;
	float distanceY = targetPos.y - renderPos.y;

	if (distanceX * distanceX + distanceY * distanceY < 0.5f) {
		renderPos = targetPos;
		isAnimating = false;
	}
}
