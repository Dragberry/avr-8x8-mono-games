#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>

class Game {

protected:
	uint16_t time;

	virtual void increment() = 0;

public:
	virtual ~Game();

	virtual bool isGoingOn();

	Game& operator++ ();

	virtual void buildImage(uint8_t** image) = 0;
};

#endif
