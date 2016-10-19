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
	int f=0;
	const int FRAMES = 10;
	int aux;

	//
	// show initial score (zero)
	//
	disp_show_decimal(sum);

	for (int i = 0; i < FRAMES; i++) {
		bsk_get_throw(bsk_game.frames[i], 0);
		bsk_get_throw(bsk_game.frames[i], 1);
		if (bsk_valid_frame(bsk_game.frames[i]) == 0) {
			sum = sum + bsk_get_throw(bbsk_game.frames[i], 0);
			disp_show_decimal(sum);
			delay_ls();
			if (bsk_get_throw(bbsk_game.frames[i], 0) < 10) {
				sum = sum + bsk_get_throw(bbsk_game.frames[i], 1);
				disp_show_decimal(sum);
				delay_ls();
			}
		}
	}

	return sum;
}
