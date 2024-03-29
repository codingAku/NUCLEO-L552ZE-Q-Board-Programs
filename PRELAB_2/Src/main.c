/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

uint32_t wait_millisecond = 1000;
uint32_t wait_counter = 0;

int main(void) {
	*((uint32_t*)(0x40021000 + 0x4C)) |= 0x01 << 1;

	*((uint32_t*)(0x42020400 + 0x08)) &= ~(0x03 << (7 * 2));
	*((uint32_t*)(0x42020400 + 0x08)) |= (0x01 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x04)) &= ~(0x01 << 7);

	*((uint32_t*)(0x42020400 + 0x0C)) &= ~(0x03 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x00)) &= ~(0x03 << (7 * 2));
	*((uint32_t*)(0x42020400 + 0x00)) |= (0x01 << (7 * 2));

	*((uint32_t*)(0x42020400 + 0x18)) |= (0x01 << 7);

	while(1) {
		volatile int index;

		*((uint32_t*)(0x42020400 + 0x18)) |= (0x01 << 7);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;

		*((uint32_t*)(0x42020400 + 0x18)) |= ((0x01 << 7) << 16);

		for(index=0;index<wait_millisecond*333;index++);
		wait_counter = wait_counter + 1;

	}
}
