#include "exitCard.hpp"
#include "card.hpp"

ExitCard::ExitCard() {
	name = "EXIT";
	textureId = TextureId::DOOR_0;
}

void ExitCard::RenderContent(Vector2 position, Vector2 cellSize,
							 TextureManager &tm) {}

std::string ExitCard::GetTopText() const {
	return name;
}

std::string ExitCard::GetBottomText() const {
	return {};
}

InteractionResult ExitCard::Interact(PlayerCard &player) {
	return {
		.replace{true}, .replaceInto{nullptr}, .event{GameEvent::ADVANCE_ROOM}};
}
