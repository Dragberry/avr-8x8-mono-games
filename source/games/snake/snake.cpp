#include "snake.h"

Snake::Snake(uint8_t fieldHeight, uint8_t fieldWidth, uint8_t initLength, Direction direction) {
	this->fieldHeight = fieldHeight;
	this->fieldWidth = fieldWidth;
	this->maxLength = fieldHeight * fieldWidth;
	this->length = initLength;
	this->direction = direction;
	this->body = new SnakeSection[maxLength];
	for (uint16_t n = length; n > 0; n--) {
		SnakeSection* section = &body[length - n];
		section->x = n - 1;
		section->y = 0;
		section->direction = direction;
	}
	this->tail = body[length - 1];
}

Snake::~Snake() {
	delete []body;
}

bool Snake::isHere(uint8_t row, uint8_t column) {
	for (uint16_t n = 0; n < length; n++) {
		SnakeSection* section = &body[n];
		if (section->x == column && section->y == row) {
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
	for (uint16_t n = 0; n < length; n++) {
		if (n == 0) {
			currentDirection = direction;
		} else {
			currentDirection = leaderDirection;
		}
		SnakeSection* section = &body[n];
		if (n == length - 1) {
			tail = *section;
		}
		leaderDirection = section->direction;
		section->direction = currentDirection;
		section->move(fieldHeight - 1, fieldWidth - 1);
	}
}

bool Snake::eat(const Food &food) {
	if (food.x == body[0].x && food.y == body[0].y) {
		body[length++] = tail;
		return true;
	}
	return false;
}
