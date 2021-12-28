/*
 * GPIOController.h
 *
 *  Created on: Dec 26, 2021
 *  Author: Luke
 *
 *	Buttons Register:
 *
 *	|7|6|5|4|3|2|1|0|
 *	| | | | | | | | |
 *
 *	Button 0: Action ("A" button)
 *	Button 1: Secondary ("B" button)
 *	Button 2: Up
 *	Button 3: Right
 *	Button 4: Down
 *	Button 5: Up
 *	Button 6:
 *	Button 7:
 */

#ifndef INC_GPIOCONTROLLER_H_
#define INC_GPIOCONTROLLER_H_

#include "stm32f4xx_hal.h"

#include "stdlib.h"

#define GPIOCONTROLLER_BUTTON_ACTION	0x01
#define GPIOCONTROLLER_BUTTON_SECONDARY 0x02
#define GPIOCONTROLLER_BUTTON_UP		0x04
#define GPIOCONTROLLER_BUTTON_RIGHT		0x08
#define GPIOCONTROLLER_BUTTON_DOWN		0x10
#define GPIOCONTROLLER_BUTTON_LEFT		0x20

void GPIOController_init();
uint8_t GPIOController_getButtonState();
uint8_t GPIOController_readButtonPressed(uint8_t button);
uint8_t GPIOController_readButtonReleased(uint8_t button);

void GPIOController_debounceButton();

#endif /* INC_GPIOCONTROLLER_H_ */
