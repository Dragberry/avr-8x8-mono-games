#include "../../source/games/game.h"

Game::~Game() {}

Game& Game::operator++ () {
	time++;
	increment();
	return *this;
}
