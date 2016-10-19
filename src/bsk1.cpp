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
// get_throw reads the BSK pin counting device and returns
// the number of knocked pins via the "pFrame" structure
//
// return value for the subroutine is:
//   ERR_PARAM_NULL if pFrame is zero/NULL
//   ERR_BAD_THROW if index is not 1 or 2
//   1 for reading the first throw
//   2 for reading the second throw
//   ERR_READ_FAILED if i2c_read returns other than 1
//
int bsk_get_throw(bsk_frame_t* pFrame,int index)
{
	char* data = new char[1];
	if ( 0==pFrame )
	{
		return ERR_PARAM_NULL;
	}
	if ( index!=1 || index!=2 )
		return ERR_BAD_THROW;
	if( i2c_read(0x90,0,0,data,1)==1 )
	{// Here, I do not know how to read the datum.
	 // I do not know how to call the function i2c_read().
		if ( 1==index )
		{

			pFrame->first_throw = *data + '0';
			return 1;
		}
		if ( 2==index && 10!=pFrame->first_throw )
		{

			pFrame->second_throw = *data + '0';
			return 2;
		}
	}
	return ERR_BAD_THROW;
}
