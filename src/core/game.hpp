#pragma once

#include <raylib.h>

#include "board.hpp"

class Game {
  public:
	void Init();

	void Update();
	void Render();

  private:
	Board board;
};
