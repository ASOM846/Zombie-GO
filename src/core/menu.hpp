#pragma once

#include "button.hpp"

class Menu {
  public:
	void Init();
	void Update();
	void Render();

	bool ShouldGameStart();

	Button startGameButton;

	bool shouldGameStart;
};
