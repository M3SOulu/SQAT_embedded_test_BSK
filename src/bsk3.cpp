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
// return "0" (zero) of whole frame is valid
//
// return -1 if pFrame (pointer) is invalid (NULL)
//
// return 1 if frame first throw is bad
//
// return 2 if second throw is bad
//
// return 3 if sum is bad
//
int bsk_valid_frame(bsk_frame_t* pFrame)
{
	if ( 0==pFrame ){
		return -1;
	}
	int firstThrow = pFrame->first_throw;
	int secondThrow = pFrame->second_throw;
	if(pFrame->first_throw > 10 || pFrame->first_throw < 0){
		return 1;
	}
	if(pFrame->second_throw > 10 || pFrame->second_throw < 0){
		return 2;
	}
	if(pFrame->first_throw + pFrame->second_throw > 10){
		return 3;
	}
	return -1;
}
