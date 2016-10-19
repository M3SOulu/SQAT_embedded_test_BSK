/*
 * display.h
 *
 *  Created on: Jun 6, 2016
 *      Author: timppa
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define ADDR_HT16K33       0x70

#define HT16K33_8_16_DUTY    		0x08

#define DISP_ERR_OVERFLOW  -1
#define DISP_ERR_UNDERFLOW -2
#define DISP_ERR_ILLEGAL   -3

int disp_off();

#define DISP_SHOW_ALL   1
#define DISP_SHOW_NONE  0

#define SEGMENT_NONE 0
#define SEGMENT_ALL  0xFF

#define SEGMENT_0    63
#define SEGMENT_1     6

int disp_off();
int disp_on(int alloff);
void disp_reset(int alloff);

int disp_digit_of(int value,unsigned int n);
int disp_show_decimal( int value );

#endif /* DISPLAY_H_ */
