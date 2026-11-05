#pragma once

#include "../entity/card/card.hpp"
#include <raylib.h>

#include "../entity/card/playerCard.hpp"

#include <algorithm>
#include <string>

namespace gfx {
inline float userFontScale = 1.00f;
inline int cellWidth;  //= 266; proportions are 1/3 : 1
inline int cellHeight; //=200;

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

	if (card.gradientColor.a > 0) {
		drawRect(position.x, position.y, width, height, card.gradientColor);
	}

	if (auto *playerCard = dynamic_cast<PlayerCard *>(&card)) {
		drawRect(position.x, position.y, width, height, BLUE);
	}

	// Main metal surface
	drawRect(position.x + 3, position.y + 3, width - 6, height - 6, panel);

	// Highlighted card
	if (card.isHighlited) {
		// drawRect(position.x, position.y, width, height, {105, 130, 65, 180});
		drawRect(position.x, position.y, width, height,
				 ColorAlpha(card.highlightColor, 180));
	}

	// Card name
	const int fontSize = std::max(1, static_cast<int>(20 * userFontScale));

	const char *text = card.GetTopText().c_str();

	const int textWidth = MeasureText(text, fontSize);
	const float nameOffsetY = 16.0f * userFontScale;

	Vector2 namePos =
		transform(centerX - textWidth / 2.0f, position.y + nameOffsetY);

	// Dark text shadow
	DrawText(text, static_cast<int>(namePos.x + 1),
			 static_cast<int>(namePos.y + 2),
			 std::max(1, static_cast<int>(fontSize * s)), shadow);

	DrawText(text, static_cast<int>(namePos.x), static_cast<int>(namePos.y),
			 std::max(1, static_cast<int>(fontSize * s)), textColor);

	// Top separator
	const float topSepY = position.y + 42 * userFontScale;

	// drawLine({position.x + 14, topSepY}, {position.x + width - 14, topSepY},
	// 2, 		 RED);

	// Bottom separator
	const float bottomSepY = position.y + height - 46 * userFontScale;

	// drawLine({position.x + 14, bottomSepY},
	// 		 {position.x + width - 14, bottomSepY}, 2, RED);

	// Card value
	std::string valueStr = card.GetBottomText();

	const int valueFontSize = std::max(1, static_cast<int>(24 * userFontScale));

	const int valueWidth = MeasureText(valueStr.c_str(), valueFontSize);

	const float valueOffsetY = 8.0f * userFontScale;
	Vector2 valuePos =
		transform(centerX - valueWidth / 2.0f, bottomSepY + valueOffsetY);

	DrawText(valueStr.c_str(), static_cast<int>(valuePos.x),
			 static_cast<int>(valuePos.y),
			 std::max(1, static_cast<int>(valueFontSize * s)), textColor);

	// Card artwork – dopasowanie tekstury z zachowaniem proporcji
	const Texture2D &texture = tm.get(card.textureId);

	const float texturePadding = 12.0f * userFontScale;
	const float textureGap = 8.0F * userFontScale;

	const float availableWidth = width - texturePadding * 2.0f;
	const float availableHeight = bottomSepY - topSepY - textureGap * 2.0f;

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

	if (auto *playerCard = dynamic_cast<PlayerCard *>(&card)) {
		if (playerCard->currentWeapon) {
			float rectSize = 5;

			auto weapon = playerCard->currentWeapon;

			float numberOfSpacings = weapon->maxDurability + 1;

			float spacingLength =
				((width - (rectSize * weapon->maxDurability)) /
				 numberOfSpacings);

			for (int i = 0; i < weapon->maxDurability; i++) {
				float x = spacingLength * (i + 1) + rectSize * i;

				DrawRectangle(position.x + x, bottomSepY, rectSize, rectSize,
							  shadow);
			}

			for (int i = 0; i < weapon->currentDurability; i++) {
				float x = spacingLength * (i + 1) + rectSize * i;

				DrawRectangle(position.x + x, bottomSepY, rectSize, rectSize,
							  textColor);
			}

			const Texture2D &weaponTex =
				tm.get(playerCard->currentWeapon->textureId);

			float weaponBaseScale = 3.0f;
			float wDrawWidth = weaponTex.width * weaponBaseScale;
			float wDrawHeight = weaponTex.height * weaponBaseScale;

			// Pozycja lokalna względem środka karty
			float localX = centerX - (wDrawWidth / 2.0f) - (cellSize.x / 4.0f);
			float localY = centerY - (wDrawHeight / 2.0f) - 15.0f;

			Vector2 weaponPos = transform(localX, localY);

			Rectangle weaponSource = {0.0f, 0.0f,
									  static_cast<float>(weaponTex.width),
									  static_cast<float>(weaponTex.height)};

			Rectangle weaponDest = {weaponPos.x, weaponPos.y, wDrawWidth * s,
									wDrawHeight * s};

			DrawTexturePro(weaponTex, weaponSource, weaponDest, {0.0f, 0.0f},
						   0.0f, RAYWHITE);
		}
	}
}

inline void DrawButton(const Rectangle &dst, const char *text,
					   float shadowOffset, const Font &font) {

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

	const float width = dst.width;
	const float height = dst.height;

	// Card shadow
	DrawRectangleRec({dst.x + 5, dst.y + 6, dst.width, dst.height}, shadow);

	// card border
	DrawRectangleRec(dst, shadow);

	// Main metal surface
	DrawRectangle(dst.x + 3, dst.y + 3, width - 6, height - 6, panel);

	// Button text
	float fontSize = 20.0f * gfx::userFontScale;

	const float fontSpacing = 1.0f;

	Vector2 textSize = MeasureTextEx(font, text, fontSize, fontSpacing);

	float textX = dst.x + dst.width / 2.0f - textSize.x / 2.0f;
	float textY = dst.y + dst.height / 2.0f - textSize.y / 2.0f;

	DrawTextEx(font, text, {textX + 1, textY + 2}, fontSize, fontSpacing,
			   {0, 0, 0, 100});

	DrawTextEx(font, text, {textX, textY}, fontSize, fontSpacing, textColor);
}
} // namespace gfx
