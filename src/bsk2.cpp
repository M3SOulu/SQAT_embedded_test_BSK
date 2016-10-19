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
	sum += (pGame->frames)[frames].first_throw;
	if( (pGame->frames)[frames].second_throw!=0 || (pGame->frames)[frames].second_throw!=0 )
		sum += (pGame->frames)[frames].second_throw;
	if( sum>10 )
		return ERR_BAD_FRAME;
	return sum;
}
