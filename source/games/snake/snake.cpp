#include "snake.h"

Snake::Snake(uint8_t fieldHeight, uint8_t fieldWidth, uint8_t initLength, Direction direction) {
	this->fieldHeight = fieldHeight;
	this->fieldWidth = fieldWidth;
	this->maxLength = fieldHeight * fieldWidth;
	this->length = initLength;
	this->direction = direction;
	this->body = new SnakeSection[maxLength];
	for (uint16_t n = length - 1; n != 0; n--) {
		body[n].x = n;
		body[n].y = 0;
		body[n].direction = direction;
	}

}

Snake::~Snake() {
	delete []body;
}

bool Snake::isHere(uint8_t row, uint8_t column) {
	for (uint16_t n = 0; n < length; n++) {
		if (body[n].x == column && body[n].y == row) {
			return true;
		}
	}
	return false;
}

void Snake::setDirection(Direction direction) {
	this->direction = direction;
}

Direction Snake::getDirection() {
	return direction;
}

void Snake::move() {
	Direction leaderDirection = direction;
	Direction currentDirection;
	for (uint16_t n = length; n != 0; n--) {
		if (n == length) {
			currentDirection = direction;
		} else {
			currentDirection = leaderDirection;
		}
		SnakeSection* section = &body[n - 1];
		leaderDirection = section->direction;
		section->direction = currentDirection;
		section->move(fieldHeight - 1, fieldWidth - 1);
	}
}
