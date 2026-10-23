#include "game.hpp"

void Game::Init() {
	board.Init();
}

void Game::Update() {
	board.Update();
}

void Game::Render() {
	board.Render();
}
