#pragma once

#include "../entity/card/card.hpp"
#include <raylib.h>

namespace gfx {
void DrawCardBase(float centerX, float centerY, Vector2 position,
				  Vector2 cellSize, TextureManager &tm, Card &card) {

	const float s = card.scale;

	auto transform = [&](float x, float y) -> Vector2 {
		return {centerX + (x - centerX) * s, centerY + (y - centerY) * s};
	};

	auto drawRect = [&](float x, float y, float w, float h, Color color) {
		Vector2 p = transform(x, y);

		DrawRectangle(static_cast<int>(p.x), static_cast<int>(p.y),
					  static_cast<int>(w * s), static_cast<int>(h * s), color);
	};

	auto drawLine = [&](Vector2 start, Vector2 end, float thickness,
						Color color) {
		Vector2 a = transform(start.x, start.y);
		Vector2 b = transform(end.x, end.y);

		DrawLineEx(a, b, thickness * s, color);
	};

	auto drawCircle = [&](float x, float y, float radius, Color color) {
		Vector2 p = transform(x, y);
		DrawCircleV(p, radius * s, color);
	};

	int radius = cellSize.x / 2 * card.scale;
	int size = radius * 2;

	const auto shadow = Color{0, 0, 0, 100};
	const auto darkWood = Color{60, 30, 15, 255};
	const auto parchment = Color{220, 200, 170, 255};
	const auto goldAccent = Color{180, 130, 40, 255};

	const float width = cellSize.x;
	const float height = cellSize.y;

	drawRect(position.x + 4, position.y + 4, width, height, shadow);
	drawRect(position.x, position.y, width, height, darkWood);

	const float border = 6;

	drawRect(position.x + border, position.y + border, width - 2 * border,
			 height - 2 * border, parchment);

	Vector2 gradTL = transform(position.x + border, position.y + border);
	Vector2 gradTR =
		transform(position.x + width - border, position.y + border);
	Vector2 gradBR =
		transform(position.x + width - border, position.y + height - border);
	Vector2 gradBL =
		transform(position.x + border, position.y + height - border);

	Color topColor = card.gradientColor;
	// Color bottomColor = {card.gradientColor.r, card.gradientColor.g,
	// 					 card.gradientColor.b, 0};
	Color bottomColor = BLANK;

	DrawRectangleGradientEx({gradTL.x, gradTL.y, (width - 2 * border) * s,
							 (height - 2 * border) * s},
							topColor, bottomColor, topColor, bottomColor);

	const float innerMargin = border + 4;

	DrawRectangleLinesEx(
		{transform(position.x + innerMargin, position.y + innerMargin).x,
		 transform(position.x + innerMargin, position.y + innerMargin).y,
		 (width - 2 * innerMargin) * s, (height - 2 * innerMargin) * s},
		2 * s, goldAccent);

	const float cornerLen = 16.0f;
	const float thick = 4.0f;
	const float p = innerMargin;

	Vector2 tl = {position.x + p, position.y + p};
	Vector2 tr = {position.x + width - p, position.y + p};
	Vector2 bl = {position.x + p, position.y + height - p};
	Vector2 br = {position.x + width - p, position.y + height - p};

	drawLine(tl, {tl.x + cornerLen, tl.y}, thick, goldAccent);
	drawLine(tl, {tl.x, tl.y + cornerLen}, thick, goldAccent);

	drawLine(tr, {tr.x - cornerLen, tr.y}, thick, goldAccent);
	drawLine(tr, {tr.x, tr.y + cornerLen}, thick, goldAccent);

	drawLine(bl, {bl.x + cornerLen, bl.y}, thick, goldAccent);
	drawLine(bl, {bl.x, bl.y - cornerLen}, thick, goldAccent);

	drawLine(br, {br.x - cornerLen, br.y}, thick, goldAccent);
	drawLine(br, {br.x, br.y - cornerLen}, thick, goldAccent);

	const float niteRadius = 3;

	drawCircle(tl.x, tl.y, niteRadius, darkWood);
	drawCircle(tr.x, tr.y, niteRadius, darkWood);
	drawCircle(bl.x, bl.y, niteRadius, darkWood);
	drawCircle(br.x, br.y, niteRadius, darkWood);

	const int fontSize = 20;
	const char *text = card.name.c_str();

	const int textWidth = MeasureText(text, fontSize);

	Vector2 namePos = transform(centerX - textWidth / 2.0f, position.y + 16);

	DrawText(text, static_cast<int>(namePos.x), static_cast<int>(namePos.y),
			 std::max(1, static_cast<int>(fontSize * s)), {40, 20, 10, 255});

	const float sepY = position.y + 42;

	drawLine({position.x + 14, sepY}, {position.x + width - 14, sepY}, 2,
			 goldAccent);

	drawCircle(position.x + 14, sepY, 2, darkWood);
	drawCircle(position.x + width - 14, sepY, 2, darkWood);

	const float sepYBottom = position.y + height - 46;

	drawLine({position.x + 14, sepYBottom},
			 {position.x + width - 14, sepYBottom}, 2, goldAccent);

	drawCircle(position.x + 14, sepYBottom, 2, darkWood);
	drawCircle(position.x + width - 14, sepYBottom, 2, darkWood);

	std::string valueStr = card.GetValueText();

	const int valueFontSize = 24;
	const int valueWidth = MeasureText(valueStr.c_str(), valueFontSize);

	Vector2 valuePos = transform(centerX - valueWidth / 2.0f, sepYBottom + 8);

	DrawText(valueStr.c_str(), static_cast<int>(valuePos.x),
			 static_cast<int>(valuePos.y),
			 std::max(1, static_cast<int>(valueFontSize * s)),
			 {50, 30, 20, 255});

	const Texture2D &texture = tm.get(card.textureId);
	const float textureScale = 3.0f;

	float drawX = centerX - (texture.width * textureScale) / 2.0f;
	float drawY =
		centerY - (texture.height * textureScale) / 2.0f - (5 * textureScale);

	Vector2 texturePos = transform(drawX, drawY);

	DrawTextureEx(texture, texturePos, 0.0f, textureScale * s, RAYWHITE);
}
} // namespace gfx
