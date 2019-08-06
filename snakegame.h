#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_

#include "game.h"

class SnakeGame : public Game {

public:
	SnakeGame(uint8_t height, uint8_t width);

	~SnakeGame();

	void increment();
};

#endif
