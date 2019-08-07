#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#include "../../source/common/utils.h"

class Screen {

private:
	uint8_t sectionHeight;
	uint8_t sectionWidth;
	uint8_t sectionsHeight;
	uint8_t sectionsWidth;
	uint8_t height;
	uint8_t width;
	uint8_t currentRow;
	uint8_t** picture;

	void reset();

public:
	Screen(uint8_t sectionHeight, uint8_t sectionWidth, uint8_t sectionsHeight, uint8_t sectionsWidth);
	~Screen();

	template <class L> void loadImage(L load) {
		reset();
		load(picture);
	}

	void drawRow(void (*sendByte)(const uint8_t &));

	uint8_t getHeight();
	uint8_t getWidth();
};

#endif
