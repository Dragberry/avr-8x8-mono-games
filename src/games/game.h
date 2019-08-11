#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>

class Game {

protected:
	uint16_t time;

	virtual void increment() = 0;
	virtual void onAction() = 0;

public:
	struct Buttons {
		uint8_t A = 0;
		uint8_t B = 0;
		uint8_t C = 0;
		uint8_t D = 0;
	} buttons;

	virtual ~Game();

	virtual bool isGoingOn();

	Game& operator++ ();

	virtual void buildImage(uint8_t** image) = 0;

	template <class S>
	void setButtonState(S setState) {
		setState(&buttons);
		onAction();
	}
};

#endif
