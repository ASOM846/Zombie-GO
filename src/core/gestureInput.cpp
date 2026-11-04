#include "gestureInput.hpp"
#include <cmath>
#include <raymath.h>
void GestureInput::Update() {
	lastGesture = currentGesture;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		touchStartPos = GetMousePosition();
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		touchEndPos = GetMousePosition();
		currentGesture = InterprateGesture();
		lastGesture = -1;
	}
}

int GestureInput::GetGestureRecorded() {
	return currentGesture;
}

int GestureInput::GetLastGestureRecorded() {
	return lastGesture;
}

const Vector2 &GestureInput::GetTouchPointStart() {
	return touchStartPos;
}

int GestureInput::InterprateGesture() {
	Vector2 diff = Vector2Subtract(touchEndPos, touchStartPos);

	if (Vector2Distance(touchStartPos, touchEndPos) <= 50)
		return GESTURE_NONE;

	if (std::abs(diff.x) > std::abs(diff.y)) {
		return diff.x > 0 ? GESTURE_SWIPE_RIGHT : GESTURE_SWIPE_LEFT;
	}

	return diff.y > 0 ? GESTURE_SWIPE_DOWN : GESTURE_SWIPE_UP;
}
