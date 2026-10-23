#pragma once

#include <raylib.h>
#include <vector>

class Board {
  public:
	void Init();

	void Update();
	void Render();

  private:
	void RenderCell();

	std::vector<std::vector<int>> board;

	const int boardY = 3;
	const int boardX = 3;

	const int cellHeight = 150;
	const int cellWidth = 100;

	const int spacing = 100;
};
