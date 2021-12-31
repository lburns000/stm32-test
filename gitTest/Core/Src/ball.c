/*
 * ball.c
 *
 *  Created on: Dec 31, 2021
 *      Author: Luke
 */

#include "ball.h"

extern UART_HandleTypeDef huart2;

typedef struct {
	int xPos;
	int yPos;
	int xPrev;
	int yPrev;
} Ball;

Ball myBall;

uint8_t ball_init() {
	myBall.xPos = WIDTH >> 1;
	myBall.yPos = HEIGHT >> 1;	// Draw ball in center of screen
	myBall.xPrev = myBall.xPos;
	myBall.yPrev = myBall.yPos;
}

void ball_draw() {
	char buffer[50];
	sprintf(buffer, "Erasing circle at (%03d, %03d)\n", myBall.xPrev, myBall.yPrev);
	HAL_UART_Transmit(&huart2, buffer, 29, 10);
	SSD1306_DrawFilledCircle(myBall.xPrev, myBall.yPrev, 2, 0);	// Clear previous image

	sprintf(buffer, "Drawing circle at (%03d, %03d)\n\n", myBall.xPos, myBall.yPos);
	HAL_UART_Transmit(&huart2, buffer, 30, 10);
	SSD1306_DrawFilledCircle(myBall.xPos, myBall.yPos, 2, 1);
}

void ball_setPosition(int x, int y) {
	myBall.xPrev = myBall.xPos;
	myBall.yPrev = myBall.yPos;
	myBall.xPos = x;
	myBall.yPos = y;
}

void ball_setX(int x) {
	myBall.xPrev = myBall.xPos;
	myBall.yPrev = myBall.yPos;
	myBall.xPos = x;
}

void ball_setY(int y) {
	myBall.xPrev = myBall.xPos;
	myBall.yPrev = myBall.yPos;
	myBall.yPos = y;
}

int ball_getX() {
	return myBall.xPos;
}

int ball_getY() {
	return myBall.yPos;
}

uint8_t ball_destroy() {

}
