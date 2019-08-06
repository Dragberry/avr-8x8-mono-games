#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_

#include "game.h"

class SnakeGame : public Game {

private:
	uint8_t height;
	uint8_t width;

	uint8_t x = 0;
	uint8_t y = 0;

public:
	SnakeGame(uint8_t height, uint8_t width);

	~SnakeGame();

	void increment();

	void buildImage(uint8_t** image);
};

#endif
