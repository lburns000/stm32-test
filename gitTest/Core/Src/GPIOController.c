/*
 * GPIOController.c
 *
 *  Created on: Dec 26, 2021
 *      Author: Luke
 */


#include "GPIOController.h"

typedef struct {
	uint8_t status;
	uint8_t initialized;
} GPIOController_t;

GPIOController_t GPIOController;

void GPIOController_init() {
	GPIOController.initialized = 0;
	GPIOController.status = 0;
	GPIOController_getButtonState();

	GPIOController.initialized = 1;
}

uint8_t GPIOController_getButtonState() {
	GPIOController.status = ~(GPIOC->IDR);	// Invert for active-low buttons
	GPIOController_debounceButton();
	return GPIOController.status;
}

uint8_t GPIOController_readButtonPressed(uint8_t button) {
	GPIOController_getButtonState();
	return (button | GPIOController.status);
}

uint8_t GPIOController_readButtonReleased(uint8_t button) {
	GPIOController_getButtonState();
	return (!(button | GPIOController.status));
}

void GPIOController_debounceButton() {
	HAL_Delay(50);
}
