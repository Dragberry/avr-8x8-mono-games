#include "snakegame.h"

#include <stdlib.h>

SnakeGame::SnakeGame(uint8_t height, uint8_t width) {
	this->isImageBuilt = false;
	this->height = height;
	this->width = width;
	this->snake = new Snake(height, width, 4, Direction::Right);
	this->food = NULL;
	this->state = true;
}

SnakeGame::~SnakeGame() {
	delete food;
	delete snake;
}

bool SnakeGame::isGoingOn() {
	return state && snake->getLength() < 10;
}

void SnakeGame::onAction() {
	if (buttons.C) {
		snake->turnLeft();
	}
	if (buttons.B) {
		snake->turnRight();
	}
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
	if (time % (rand() % 5 == 0)  == 0) {
		if (rand() % 2 == 0) {
			snake->turnRight();
		} else {
			snake->turnLeft();
		}
	}
	snake->move();
	if (!snake->isAlive()) {
		state = false;
		return;
	}
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
