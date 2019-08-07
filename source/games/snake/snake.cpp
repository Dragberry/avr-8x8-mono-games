#include "snake.h"

Snake::Snake(uint8_t fieldHeight, uint8_t fieldWidth, uint8_t initLength, Direction direction) {
	this->fieldHeight = fieldHeight;
	this->fieldWidth = fieldWidth;
	this->maxLength = fieldHeight * fieldWidth;
	this->length = initLength;
	this->direction = direction;
	this->body = new SnakeSection[maxLength];
	for (uint16_t n = 0; n < length; n++) {
		body[n].x = n;
		body[n].y= 0;
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
	Direction currentDirection;
	Direction nextDirection;
	for (uint16_t n = 0; n < length; n++) {
		if (n == 0) {
			nextDirection = direction;
		} else {
			nextDirection = currentDirection;
		}
		currentDirection = body[n].direction;
		switch (nextDirection) {
		case Up:
			moveUp(&(body[n]));
			break;
		case Right:
			moveRight(&(body[n]));
			break;
		case Down:
			moveDown(&(body[n]));
			break;
		case Left:
			moveLeft(&(body[n]));
			break;
		}
		body[n].direction = nextDirection;
	}
}

void Snake::moveUp(SnakeSection* section) {
	uint8_t y = section->y;
	if (y == 0) {
		y = fieldHeight - 1;
	} else {
		y--;
	}
	section->y = y;
}

void Snake::moveRight(SnakeSection* section) {
	uint8_t x = section->x;
	if (x == fieldWidth - 1) {
		x = 0;
	} else {
		x++;
	}
	section->x = x;

}

void Snake::moveDown(SnakeSection* section) {
	uint8_t y = section->y;
	if (y == fieldHeight - 1) {
		y = 0;
	} else {
		y++;
	}
	section->y = y;

}

void Snake::moveLeft(SnakeSection* section) {
	uint8_t x = section->x;
	if (x == 0) {
		x = fieldWidth - 1;
	} else {
		x--;
	}
	section->x = x;
}
