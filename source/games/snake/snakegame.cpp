#include "snakegame.h"

#include <stdlib.h>
#include "snake.h"

SnakeGame::SnakeGame(uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
	this->snake = new Snake(height, width, 4, Direction::Right);
}

SnakeGame::~SnakeGame() {
	delete snake;
}

void SnakeGame::increment() {
	if (time % 4 == 0) {
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
}

void SnakeGame::buildImage(uint8_t** image) {
	for (uint8_t row = 0; row < height; row++) {
		for (uint8_t cell = 0; cell < width; cell++) {
			image[row][cell] = snake->isHere(row, cell) ? 1 : 0;
		}
	}
}
