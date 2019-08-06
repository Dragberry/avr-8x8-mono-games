#include <stdlib.h>
#include "snakegame.h"

SnakeGame::SnakeGame(uint8_t height, uint8_t width) {
	this->height = height;
	this->width = width;
}

SnakeGame::~SnakeGame() {}

void SnakeGame::increment() {
	if (rand() % 4 == 0) {
		x++;
		x = x == width ? 0 : x;
	} else {
		y++;
		y = y == height ? 0 : y;
	}
}

void SnakeGame::buildImage(uint8_t** image) {
	for (uint8_t row = 0; row < height; row++) {
		for (uint8_t cell = 0; cell < width; cell++) {
			image[row][cell] = row == y && cell == x ? 1 : 0;
		}
	}
}
