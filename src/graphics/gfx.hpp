#pragma once

#include "../entity/card/card.hpp"
#include <raylib.h>

#include <algorithm>
#include <string>

namespace gfx {
inline float userScale = 1.0f;

inline void DrawCardBase(float centerX, float centerY, Vector2 position,
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

	// Background – główne tło gry
	const Color background = {32, 36, 38, 255};

	// Panel – karty, przyciski, panele UI
	const Color panel = {56, 62, 64, 255};

	// Border – ramki, separatory
	const Color border = {91, 98, 99, 255};

	// Primary Text – nazwy, nagłówki
	const Color textColor = {210, 212, 208, 255};

	// Secondary Text – opisy, mniej ważne informacje
	const Color secondaryText = {165, 170, 170, 255};

	// Shadow – cienie pod kartami i przyciskami
	const Color shadow = {0, 0, 0, 120};

	const float width = cellSize.x;
	const float height = cellSize.y;

	// Card shadow
	drawRect(position.x + 5, position.y + 6, width, height, shadow);

	// card border
	drawRect(position.x, position.y, width, height, border);

	// Main metal surface
	drawRect(position.x + 3, position.y + 3, width - 6, height - 6, panel);

	// Highlighted card
	if (card.isHighlited) {
		drawRect(position.x, position.y, width, height, {105, 130, 65, 180});
	}

	// Card name
	const int fontSize = 20;
	const char *text = card.name.c_str();

	const int textWidth = MeasureText(text, fontSize);

	Vector2 namePos = transform(centerX - textWidth / 2.0f, position.y + 16);

	// Dark text shadow
	DrawText(text, static_cast<int>(namePos.x + 1),
			 static_cast<int>(namePos.y + 2),
			 std::max(1, static_cast<int>(fontSize * s)), shadow);

	DrawText(text, static_cast<int>(namePos.x), static_cast<int>(namePos.y),
			 std::max(1, static_cast<int>(fontSize * s)), textColor);

	// Top separator
	const float topSepY = position.y + 42;

	drawLine({position.x + 14, topSepY}, {position.x + width - 14, topSepY}, 2,
			 RED);

	// Bottom separator
	const float bottomSepY = position.y + height - 46;

	drawLine({position.x + 14, bottomSepY},
			 {position.x + width - 14, bottomSepY}, 2, RED);

	// Card value
	std::string valueStr = card.GetValueText();

	const int valueFontSize = 24;
	const int valueWidth = MeasureText(valueStr.c_str(), valueFontSize);

	Vector2 valuePos = transform(centerX - valueWidth / 2.0f, bottomSepY + 8);

	DrawText(valueStr.c_str(), static_cast<int>(valuePos.x),
			 static_cast<int>(valuePos.y),
			 std::max(1, static_cast<int>(valueFontSize * s)), textColor);

	// Card artwork – dopasowanie tekstury z zachowaniem proporcji
	const Texture2D &texture = tm.get(card.textureId);

	const float texturePadding = 12.0f;

	const float availableWidth = width - texturePadding * 2.0f;
	const float availableHeight = bottomSepY - topSepY - 16.0f;

	// Skala dopasowująca teksturę do dostępnego obszaru
	const float scaleX = availableWidth / texture.width;
	const float scaleY = availableHeight / texture.height;
	const float textureScale = std::min(scaleX, scaleY);

	// Końcowe wymiary tekstury
	const float drawWidth = texture.width * textureScale;
	const float drawHeight = texture.height * textureScale;

	// Wyśrodkowanie tekstury między separatorami
	const float drawX = centerX - drawWidth / 2.0f;
	const float drawY = topSepY + 8.0f + (availableHeight - drawHeight) / 2.0f;

	Rectangle source = {0.0f, 0.0f, static_cast<float>(texture.width),
						static_cast<float>(texture.height)};

	Rectangle dest = {transform(drawX, drawY).x, transform(drawX, drawY).y,
					  drawWidth * s, drawHeight * s};

	DrawTexturePro(texture, source, dest, {0.0f, 0.0f}, 0.0f, RAYWHITE);
}

inline void DrawButton(const Rectangle &dst, const char *text,
					   float shadowOffset, const Font &font) {

	const Color shadow = {0, 0, 0, 180};
	const Color darkMetal = {23, 29, 26, 255};
	const Color metal = {48, 55, 48, 255};
	const Color dirtyPaper = {173, 166, 132, 255};
	const Color rust = {125, 65, 35, 255};
	const Color warning = {190, 153, 55, 255};
	const Color textColor = {29, 32, 25, 255};

	// Shadow
	DrawRectangle(dst.x + shadowOffset, dst.y + shadowOffset, dst.width,
				  dst.height, shadow);

	// Outer casing
	DrawRectangle(dst.x, dst.y, dst.width, dst.height, darkMetal);

	// Metal body
	DrawRectangle(dst.x + 3, dst.y + 3, dst.width - 6, dst.height - 6, metal);

	const float border = 8.0f;

	// Inner panel
	DrawRectangle(dst.x + border, dst.y + border, dst.width - 2 * border,
				  dst.height - 2 * border, dirtyPaper);

	// Warning stripe
	DrawRectangle(dst.x + border + 2, dst.y + border + 2, 5,
				  dst.height - 2 * border - 4, warning);

	// Inner border
	const float innerMargin = border + 5;

	DrawRectangleLinesEx({dst.x + innerMargin, dst.y + innerMargin,
						  dst.width - 2 * innerMargin,
						  dst.height - 2 * innerMargin},
						 2, rust);

	// Reinforced corners
	const float cornerLen = 17.0f;
	const float thick = 4.0f;
	const float p = innerMargin + 2;

	Vector2 tl = {dst.x + p, dst.y + p};
	Vector2 tr = {dst.x + dst.width - p, dst.y + p};
	Vector2 bl = {dst.x + p, dst.y + dst.height - p};
	Vector2 br = {dst.x + dst.width - p, dst.y + dst.height - p};

	DrawLineEx(tl, {tl.x + cornerLen, tl.y}, thick, warning);
	DrawLineEx(tl, {tl.x, tl.y + cornerLen}, thick, warning);

	DrawLineEx(tr, {tr.x - cornerLen, tr.y}, thick, warning);
	DrawLineEx(tr, {tr.x, tr.y + cornerLen}, thick, warning);

	DrawLineEx(bl, {bl.x + cornerLen, bl.y}, thick, warning);
	DrawLineEx(bl, {bl.x, bl.y - cornerLen}, thick, warning);

	DrawLineEx(br, {br.x - cornerLen, br.y}, thick, warning);
	DrawLineEx(br, {br.x, br.y - cornerLen}, thick, warning);

	// Rivets
	const float rivetRadius = 3.0f;

	DrawCircleV(tl, rivetRadius, darkMetal);
	DrawCircleV(tr, rivetRadius, darkMetal);
	DrawCircleV(bl, rivetRadius, darkMetal);
	DrawCircleV(br, rivetRadius, darkMetal);

	// Rust details
	DrawRectangle(dst.x + 5, dst.y + 5, 20, 4, rust);
	DrawRectangle(dst.x + dst.width - 25, dst.y + dst.height - 9, 20, 4, rust);

	// Button text
	float fontSize = 20.0f;

	if (font.texture.id != GetFontDefault().texture.id)
		fontSize = 40.0f;

	const float fontSpacing = 1.0f;

	Vector2 textSize = MeasureTextEx(font, text, fontSize, fontSpacing);

	float textX = dst.x + dst.width / 2.0f - textSize.x / 2.0f;
	float textY = dst.y + dst.height / 2.0f - textSize.y / 2.0f;

	DrawTextEx(font, text, {textX + 1, textY + 2}, fontSize, fontSpacing,
			   {0, 0, 0, 100});

	DrawTextEx(font, text, {textX, textY}, fontSize, fontSpacing, textColor);
}

} // namespace gfx
