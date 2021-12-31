/*
 * ball.h
 *
 *  Created on: Dec 31, 2021
 *      Author: Luke
 */

#include "ssd1306.h"
#include "stm32f4xx_hal.h"

#include "stdlib.h"

#ifndef INC_BALL_H_
#define INC_BALL_H_

// Screen dimensions
#define WIDTH	128
#define HEIGHT	64


uint8_t ball_init();		// Return 1 if successful, 0 if not
void ball_draw();			// Add the ball to screen buffer
void ball_setPosition(int x, int y);
void ball_setX(int x);
void ball_setY(int y);
int ball_getX();
int ball_getY();
uint8_t ball_destroy();		// Return 1 if successful, 0 if not


#endif /* INC_BALL_H_ */
