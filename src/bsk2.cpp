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
	if ( 0==pGame ){
		return ERR_PARAM_NULL;
	}

	int sum=0;
	int sumOfFrame;


	for (int i = 0; i <= frames; i++){
		sumOfFrame = bsk1.bsk_get_throw(i,1) + bsk1.bsk_get_throw(i,2);
		return sumOfFrame;
	}

	return sum;
}
