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
	bool finished = false;

	//
	// show initial score (zero)
	//
	disp_show_decimal( sum );
	delay_1s();

	while (!finished) {
		bsk_frame_t frame = bsk_game.frames[f];
		int readresult = bsk_get_throw(&frame,1);
		if (readResult != ERR_READ_FAILED) {
			if (frame.first_throw < 10) {
				int readresult = bsk_get_throw(&frame,2);
				if (readResult != ERR_READ_FAILED) {
					int validFrame = bsk_valid_frame(&frame);
					if (validFrame == 0) {
						f++;
						if (f > 9) {
							finished = true;
						}
						sum = bsk_calculate(bsk_game,f+1);
						disp_show_decimal( sum );
					}
				}
			}
		}

	}

	return -1;
}
