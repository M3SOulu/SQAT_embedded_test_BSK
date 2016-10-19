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
	//int f=0;
	//
	// show initial score (zero)
	//
	disp_show_decimal( sum );
	for (int i = 0; i < 10; ++i) { // Play 10 frames
		bsk_frame_t* currFrame = &bsk_game.frames[i];

		bsk_get_throw(currFrame, 1); // Get first throw
		while(bsk_valid_frame(currFrame) == 1){
			bsk_get_throw(currFrame, 1);
		}
		delay_1s();

		bsk_get_throw(currFrame, 2); // Get second throw
		if (bsk_valid_frame(currFrame) > 1){ // if second or sum is >10
			i--; // play frame again;
		}
		delay_1s();

		sum = bsk_calculate(&bsk_game, i+1);
		disp_show_decimal( sum );
	}

	return -1;
}
