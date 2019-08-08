#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_

#include "../game.h"
#include "snake.h"
#include "food.h"

class SnakeGame : public Game {

private:
	uint8_t height;
	uint8_t width;

	Snake* snake;
	Food* food;

	void placeFood();

public:
	SnakeGame(uint8_t height, uint8_t width);

	~SnakeGame();

	void increment();

	void buildImage(uint8_t** image);
};

#endif
