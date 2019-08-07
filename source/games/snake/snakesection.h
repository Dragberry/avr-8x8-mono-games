#ifndef SNAKESECTION_H_
#define SNAKESECTION_H_

#include <stdint.h>

struct SnakeSection {
	uint8_t x = 0;
	uint8_t y = 0;
	Direction direction;
};

#endif
