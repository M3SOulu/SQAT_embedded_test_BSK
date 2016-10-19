/*
 * bsk.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#include "hardware.h"
#include "i2c.h"
#include "delay.h"
#include "display.h"
#include "bsk.h"

/************************************************************************
 *
 *   IMPLEMENTATION BELOW
 *
 ************************************************************************/

int setThrow(unsigned char* frame, int index, unsigned char value) {
	unsigned char erase = 0xF0;

	if (!(index == 0 || index == 1))
		return -1;

	*frame = *frame & value << (4 * erase);
	*frame = *frame & value << (4 * index);
	return 0;
}

int setFrame() {
	return -1;
}

//
// play the full game
// - display points initially
// - get score for throw and spend its delay
// - get score for 2nd throw and spend its delay
// - and so on
//
int play_game()
{
	// use these variables if you wish; they are not compulsory
	int sum=0;
	bsk_game_t bsk_game;
	my_bsk_game_t mygame;
	int f=0;

	//
	// show initial score (zero)
	//
	disp_show_decimal( sum );

	char data = 0;

	for (int i = 0; i < BSK_FRAMES_IN_GAME; i++) {
		do {
			i2c_read(HW_BSK_PIN_COUNTER, 0,0, &data, 1);
		} while(data > 10);

		setThrow(&(mygame.frames[i]), 0, data);

		if (10 == data)
			continue;

		do {
			i2c_read(HW_BSK_PIN_COUNTER, 0,0, &data, 1);
		} while(data > 10);

		setThrow(&(mygame.frames[i]), 1, data);
	}

	return -1;
}
