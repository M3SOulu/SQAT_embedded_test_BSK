/*
 * bsk.h
 *
 *  Created on: Oct 11, 2016
 *      Author: timppa
 */

#ifndef BSK_H_
#define BSK_H_

#define ERR_PARAM_NULL  -1
#define ERR_BAD_THROW   -2
#define ERR_READ_FAILED -3
#define ERR_BAD_FRAME   -4

typedef struct bsk_frame {
	int first_throw = 0;
	int second_throw = 0;
} bsk_frame_t;

#define BSK_FRAMES_IN_GAME 10

typedef struct bsk_game {
	bsk_frame_t frames[BSK_FRAMES_IN_GAME];
} bsk_game_t;

int bsk_get_throw(bsk_frame_t* pFrame,int index);
int bsk_calculate(bsk_game_t* pGame,int frames);
int bsk_valid_frame(bsk_frame_t* pFrame);
int play_game();

#endif /* BSK_H_ */
