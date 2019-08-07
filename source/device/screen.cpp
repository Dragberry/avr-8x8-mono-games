#include "../../source/device/screen.h"

Screen::Screen(uint8_t sectionHeight, uint8_t sectionWidth, uint8_t sectionsHeight, uint8_t sectionsWidth) {
	this->sectionHeight = sectionHeight;
	this->sectionWidth = sectionWidth;
	this->sectionsHeight = sectionsHeight;
	this->sectionsWidth = sectionsWidth;
	this->height = sectionHeight * sectionsHeight;
	this->width = sectionWidth * sectionsWidth;
	this->picture = new uint8_t*[height];
	for (uint8_t row = 0; row < height; row++) {
		this->picture[row] = new uint8_t[width];
		for (uint8_t cell = 0; cell < width; cell++) {
			this->picture[row][cell] = 0;
		}
	}
	this->currentRow = 0;
}

Screen::~Screen() {
	for (uint8_t row = 0; row < height; row++) {
		delete picture[row];
	}
	delete picture;
}

void Screen::reset() {
	for (uint8_t row = 0; row < height; row++) {
		for (uint8_t cell = 0; cell < width; cell++) {
			this->picture[row][cell] = 0;
		}
	}
}

void Screen::drawRow(void (*sendByte)(const uint8_t &)) {
	for (uint8_t columnSection = 0; columnSection < sectionsWidth; columnSection++) {
		uint8_t cellByte = 0xFF;
		uint8_t sectionOffset = columnSection * sectionsWidth;
		for (uint8_t cell = 0; cell < sectionWidth; cell++) {
			cellByte &= ~(picture[currentRow][sectionOffset + cell] << (sectionWidth - 1 - cell));
		}
		sendByte(cellByte);
	}

	for (uint8_t rowSection = 0; rowSection < sectionsHeight; rowSection++) {
		if (currentRow / sectionHeight == rowSection) {
			sendByte(1 << (sectionHeight - 1 - currentRow % sectionHeight));
		} else {
			sendByte(0);
		}
	}

	if (currentRow++ == height) {
		currentRow = 0;
	}
}

uint8_t Screen::getHeight() {
	return height;
}

uint8_t Screen::getWidth() {
	return width;
}
