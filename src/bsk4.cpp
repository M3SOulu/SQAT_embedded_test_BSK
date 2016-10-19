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

	return -1;
}
