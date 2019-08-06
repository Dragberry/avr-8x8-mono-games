#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "screen.h"
#include "game.h"
#include "snakegame.h"

#define FREQUENCY 8000000

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_SCK PB7
#define SPI_MOSI PB5
#define SPI_SS PB4

#define SECTION_WIDTH 8
#define SECTION_HEIGHT 8

#define SECTIONS_WIDTH 1
#define SECTIONS_HEIGHT 1

#define SCREEN_WIDTH (SECTION_WIDTH * SECTIONS_WIDTH)
#define SCREEN_HEIGHT (SECTION_HEIGHT * SECTIONS_HEIGHT)

void initScreenTimer();
void initGameTimer();
void initSPI();

void resetSPI();
void confirmSPI();
void sendByte(const uint8_t &data);

void initScreen();

Screen* screen;
Game* game;

int main() {
	initSPI();
	initScreen();
	initScreenTimer();
	initGameTimer();
	sei();
	while(1);

	delete screen;
	return 0;
}

uint8_t gameTime = 0;

void initScreen() {
	screen = new Screen(SECTION_HEIGHT, SECTION_WIDTH, SECTIONS_HEIGHT, SECTIONS_WIDTH);
	game = new SnakeGame(SECTION_HEIGHT * SECTIONS_HEIGHT, SECTION_WIDTH * SECTIONS_WIDTH);
}

void initSPI() {
	SPI_DDR |= (1 << SPI_SS) | (1 << SPI_MOSI) | (1 << SPI_SCK);
	SPI_PORT |= (1 << SPI_SS);
	SPCR |= (1 << SPE) | (1 << MSTR) | (0 << DORD);
	SPSR |= (1 << SPI2X);
}

void resetSPI() {
	SPI_PORT &= ~(1 << SPI_SS);
}

void confirmSPI() {
	SPI_PORT |= (1 << SPI_SS);
}

void sendByte(const uint8_t &data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF )));
}

void initScreenTimer() {
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
	TIMSK |= (1 << OCIE0);
	OCR0 = 0x3F;
}


ISR(TIMER0_COMP_vect) {
	resetSPI();
	screen->drawRow(sendByte);
	confirmSPI();
}

void initGameTimer() {
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (0 << CS11) | (0 << CS10);
	TIMSK |= (1 << OCIE1A);
	OCR1A = 0xC35;
}

uint8_t getOffset(uint8_t &offset, uint8_t height);

ISR(TIMER1_COMPA_vect) {
	game++;
	screen->loadImage([](uint8_t** buffer) {
		uint8_t height = screen->getHeight();
		uint8_t offset = gameTime % height;

		buffer[offset][1] = 1;
		buffer[offset][2] = 1;
		buffer[offset][5] = 1;
		buffer[offset][6] = 1;

		offset = getOffset(offset, height);

		buffer[offset][0] = 1;
		buffer[offset][3] = 1;
		buffer[offset][4] = 1;
		buffer[offset][7] = 1;

		offset = getOffset(offset, height);

		buffer[offset][0] = 1;
		buffer[offset][3] = 1;
		buffer[offset][4] = 1;
		buffer[offset][7] = 1;

		offset = getOffset(offset, height);

		buffer[offset][1] = 1;
		buffer[offset][2] = 1;
		buffer[offset][5] = 1;
		buffer[offset][6] = 1;

		offset = getOffset(offset, height);

		buffer[offset][2] = 1;
		buffer[offset][5] = 1;

		offset = getOffset(offset, height);

		buffer[offset][2] = 1;
		buffer[offset][5] = 1;

		offset = getOffset(offset, height);

		buffer[offset][2] = 1;
		buffer[offset][5] = 1;

		offset = getOffset(offset, height);

		buffer[offset][3] = 1;
		buffer[offset][4] = 1;

	});
	gameTime++;
}

uint8_t getOffset(uint8_t &offset, uint8_t height) {
	return ++offset == height ? 0 : offset;
}
