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
// calculate the sum of points of "frames" first frames
//
int bsk_calculate(bsk_game_t* pGame,int frames)
{
	int sum = 0;
	if ( 0==pGame ){
		return ERR_PARAM_NULL;
	}
	/*int frame = bsk_get_throw(bsk_frame_t*, ); //No idea how to call these
	if (frame == 1) {
	//sum = (*pGame).frames();
		return sum;
	}*/



	return sum;
}
