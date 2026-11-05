#pragma once

#include "button.hpp"

class Menu {
  public:
	void Init();
	void Reset();

	void Update();
	void Render();

	[[nodiscard]] bool ShouldGameStart() const;

  private:
	void InitButtonsPositions();

	Button startGameButton;
	Button characterSelectButton;

	Button scaleDownButton;
	Button scaleUpButton;

	bool shouldGameStart;
};
