#pragma once

#include <raylib.h>
class GestureInput {
  public:
	GestureInput() = default;
	~GestureInput() = default;

	void Update();

	int GetGestureRecorded();
	int GetLastGestureRecorded();

	const Vector2 &GetTouchPointStart();

  private:
	int InterprateGesture();

	Vector2 touchStartPos;
	Vector2 touchEndPos;

	int currentGesture;
	int lastGesture;
};
