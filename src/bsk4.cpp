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

#include "swm.h"


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

int f = 0;
int sum=0;

int play_game()
{
	// use these variables if you wish; they are not compulsory

	bsk_game_t bsk_game;
	char data;
	// init, reset f_sum
	int f_sum = 0;
	// read first throw
	i2c_read(0x90, 0, 0, &data, 1);
	f_sum = data;


	if( f >= 10) {
		// do nothing
	} else {


	// calc_score; f_sum == data
		// all pins down with first throw
		if(data == 10) {
			// next frame
			f++;
			sum = sum + 10;
			} else if(data < 10){
				sum = sum + data;
				// read second throw
				i2c_read(0x90, 0, 0, &data, 1);
				f_sum = f_sum + data;
				if(data <= 10 && f_sum <= 10){
					f++;
					sum = sum + f_sum;
				// invalid input
				} else {
					// frame will not be increased
					// reset f_sum so the next read is counted as first throw
					f_sum = 0;
				}
			}

		}


		// show score
		//
		disp_show_decimal( sum );







	return -1;
}


