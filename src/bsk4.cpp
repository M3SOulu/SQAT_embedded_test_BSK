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

	//
	// show initial score (zero)
	//
	disp_show_decimal( sum );
	while( f<BSK_FRAMES_IN_GAME )
	{
		int return_number = -1;
		// get score for 1st throw
		return_number = bsk_get_throw(&((bsk_game.frames)[f]),1);
		while(return_number!=1)
			return_number = bsk_get_throw(&((bsk_game.frames)[f]),1);

		// spend its delay
		delay_1s();

		// get score for 2nd throw
		return_number = bsk_get_throw(&((bsk_game.frames)[f]),2);
		while(return_number!=1)
			return_number = bsk_get_throw(&((bsk_game.frames)[f]),2);
		sum = bsk_calculat( &bsk_game,f );

		// spend its delay
		delay_1s();

		disp_show_decimal( sum );
		++f;
	}
	return -1;
}
