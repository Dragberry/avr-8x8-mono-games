#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdint.h>
#include "direction.h"
#include "snakesection.h"

class Snake {

private:
	uint8_t fieldHeight;
	uint8_t fieldWidth;
	uint16_t maxLength;
	uint16_t length;
	SnakeSection* body;
	Direction direction;

public:
	Snake(uint8_t fieldHeight, uint8_t fieldWidth, uint8_t initLength, Direction direction);
	~Snake();

	bool isHere(uint8_t row, uint8_t column);
	void setDirection(Direction direction);
	Direction getDirection();
	void move();
	void moveUp(SnakeSection* section);
	void moveRight(SnakeSection* section);
	void moveDown(SnakeSection* section);
	void moveLeft(SnakeSection* section);
};

#endif
