#include "snakegame.h"

#include <stdlib.h>
#include "snake.h"

SnakeGame::SnakeGame(uint8_t height, uint8_t width) {
	this->isImageBuilt = false;
	this->height = height;
	this->width = width;
	this->snake = new Snake(height, width, 4, Direction::Right);
	this->food = NULL;
}

SnakeGame::~SnakeGame() {
	delete food;
	delete snake;
}

bool SnakeGame::isGoingOn() {
	return snake->getLength() < 10;
}

void SnakeGame::placeFood() {
	uint8_t newX = rand() % width;
	uint8_t newY = rand() % height;
	if (food == NULL) {
		food = new Food(newX, newY);
	} else {
		food->x = newX;
		food->y = newY;
	}
}

void SnakeGame::increment() {
	if (time % 5  == 0) {
		Direction direction = snake->getDirection();
		if (rand() % 2 == 0) {
			switch (direction) {
			case Direction::Left:
				direction = Direction::Up;
				break;
			case Direction::Up:
				direction = Direction::Right;
				break;
			case Direction::Right:
				direction = Direction::Down;
				break;
			default:
				direction = Direction::Left;
				break;
			}
		} else {
			switch (direction) {
				case Direction::Right:
					direction = Direction::Up;
					break;
				case Direction::Down:
					direction = Direction::Right;
					break;
				case Direction::Left:
					direction = Direction::Down;
					break;
				default:
					direction = Direction::Left;
					break;
				}
		}

		snake->setDirection(direction);
	}
	snake->move();
	if (food == NULL || snake->eat(*food)) {
		placeFood();
	}
}

void SnakeGame::buildImage(uint8_t** image) {
	if (isImageBuilt) {
		image[food->y][food->x] = 1;
		SnakeSection* head = snake->getHead();
		image[head->y][head->x] = 1;
		SnakeSection* tail = snake->getTail();
		image[tail->y][tail->x] = 0;
	} else {
		for (uint8_t row = 0; row < height; row++) {
			for (uint8_t cell = 0; cell < width; cell++) {
				image[row][cell] = snake->isHere(row, cell) || food->isHere(row, cell) ? 1 : 0;
			}
		}
		isImageBuilt = true;
	}
}
