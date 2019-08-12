#ifndef SNAKEGAME_H_
#define SNAKEGAME_H_

#include "food.h"
#include "snake.h"
#include "../game.h"

class SnakeGame : public Game {

private:
	bool isImageBuilt;
	uint8_t height;
	uint8_t width;

	Snake* snake;
	Food* food;

	bool state;

	void placeFood();

protected:
	void increment();
	void onAction();

public:
	SnakeGame(uint8_t height, uint8_t width);

	~SnakeGame();

	bool isGoingOn();

	void buildImage(uint8_t** image);
};

#endif
