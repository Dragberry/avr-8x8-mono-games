#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "src/device/screen.h"
#include "src/games/game.h"
#include "src/games/snake/snakegame.h"

#define CHECK_BIT(val, pos) (val & (1 << pos))

#define FREQUENCY 8000000

#define SPI_DDR DDRB
#define SPI_PORT PORTB
#define SPI_SCK PB7
#define SPI_MOSI PB5
#define SPI_SS PB4

#define BUTTONS_DDR DDRA
#define BUTTONS_PORT PORTA
#define BUTTONS_PIN PINA
#define BUTTON_A PA0
#define BUTTON_B PA1
#define BUTTON_C PA2
#define BUTTON_D PA3
#define BUTTONS_INT_DDR DDRD
#define BUTTONS_INT_PORT PORTD
#define BUTTON_INT PD2

#define SECTION_WIDTH 8
#define SECTION_HEIGHT 8

#define SECTIONS_WIDTH 1
#define SECTIONS_HEIGHT 1

#define SCREEN_WIDTH (SECTION_WIDTH * SECTIONS_WIDTH)
#define SCREEN_HEIGHT (SECTION_HEIGHT * SECTIONS_HEIGHT)

void initSPI();
void resetSPI();
void confirmSPI();
void sendByte(const uint8_t data);

void initButtons();

void initScreen();
void initScreenTimer();
void stopScreenTimer();
void shutDownScreen();

void initGameTimer();
void initGame();
void stopGameTimer();
void stopGame();

void drawScene();


Screen* screen;
Game* game;

int main() {
	initSPI();
	initScreen();
	initScreenTimer();
	initButtons();
	initGame();
	initGameTimer();
	drawScene();

	sei();

	while(1) {
		screen->clear();
		initGame();
		initGameTimer();
		while (game->isGoingOn());
		stopGame();
	}
	shutDownScreen();
	return 0;
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

void sendByte(const uint8_t data) {
	SPDR = data;
	while (!(SPSR & (1 << SPIF )));
}

void initButtons() {
	BUTTONS_DDR &= ~(1 << BUTTON_A) & ~(1 << BUTTON_B) & ~(1 << BUTTON_C) & ~(1 << BUTTON_D);
	BUTTONS_PORT |= (1 << BUTTON_A) | (1 << BUTTON_B) | (1 << BUTTON_C) | (1 << BUTTON_D);

	BUTTONS_INT_DDR &= ~(1 << BUTTON_INT);
	BUTTONS_INT_PORT |= (1 << BUTTON_INT);

	GICR |= (1 << INT0);
	MCUCR |= (1 << ISC01);
	MCUCR |= (1 << ISC00);
}

ISR(INT0_vect) {
	if (game != NULL) {
		game->setButtonState([](Game::Buttons* buttons) {
			buttons->A = CHECK_BIT(BUTTONS_PIN,  BUTTON_A);
			buttons->B = CHECK_BIT(BUTTONS_PIN,  BUTTON_B);
			buttons->C = CHECK_BIT(BUTTONS_PIN,  BUTTON_C);
			buttons->D = CHECK_BIT(BUTTONS_PIN,  BUTTON_D);
		});
	}
}

void initScreen() {
	screen = new Screen(SECTION_HEIGHT, SECTION_WIDTH, SECTIONS_HEIGHT, SECTIONS_WIDTH);
}

void drawScene() {
	screen->loadImage([](uint8_t** buffer) {
		game->buildImage(buffer);
	});
}

void initGame() {
	game = new SnakeGame(SECTION_HEIGHT * SECTIONS_HEIGHT, SECTION_WIDTH * SECTIONS_WIDTH);
}

void initScreenTimer() {
	TCCR0 |= (1 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
	TIMSK |= (1 << OCIE0);
	OCR0 = 0x3F;
}

void stopScreenTimer() {
	TCCR0 = 0;
	TIMSK &= ~(1 << OCIE0);
	OCR0 = 0;
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

void stopGameTimer() {
	TCCR1B = 0;
	TIMSK &= ~(1 << OCIE1A);
	OCR1A = 0;
}

ISR(TIMER1_COMPA_vect) {
	++(*game);
	drawScene();
}

void stopGame() {
	stopGameTimer();
	delete []game;
	game = NULL;
}

void shutDownScreen() {
	stopScreenTimer();
	delete []screen;
}
