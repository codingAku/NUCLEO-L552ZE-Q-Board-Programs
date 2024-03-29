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

typedef struct {
	volatile uint16_t MODER[2];
	volatile uint16_t OTYPER[2];
	volatile uint16_t OSPEEDR[2];
	volatile uint16_t PUPDR[2];
	volatile uint16_t IDR[2];
	volatile uint16_t ODR[2];
	volatile uint16_t BSRR[2];
	volatile uint16_t LCKR[2];
	volatile uint16_t AFR[4];
	volatile uint16_t BRR[2];
	uint16_t RESERVED[2];
	volatile uint16_t SECCFGR[2];
} GPIO_TypeDef;

uint32_t wait_milisecond = 1000;
uint32_t wait_counter = 0;

#define RCC_AHB2ENR *((volatile uint32_t *) (0x40021000 + 0x4C))

#define GPIOA	((GPIO_TypeDef *) 0x42020000)
#define GPIOB	((GPIO_TypeDef *) 0x42020400)
#define GPIOC	((GPIO_TypeDef *) 0x42020800)
int main(void) {
	RCC_AHB2ENR |= 0x01 << 0;
	RCC_AHB2ENR |= 0x01 << 1;
	RCC_AHB2ENR |= 0x01 << 2;

	GPIOA->MODER[0] &= ~(0x03); //switch mode pa0
	GPIOA->MODER[1] &= ~(0x03 << 2); // red led pa9
	GPIOA->MODER[1] |= (0x01 << 2); //red led pa9
	GPIOA->PUPDR[0] &= ~(0x03); // switch pull up
	GPIOA->PUPDR[0] |= (0x01); //switch pull up

	GPIOB->MODER[0] &= ~(0x01 << (15)); // blue led pb7
	GPIOB->MODER[0] |= (0x01 << (14)); //blue led pb7

	GPIOC->MODER[0] &= ~(0x01 << (15)); // green led pc7
	GPIOC->MODER[0] |= (0x01 << (14)); //green led pc7

	while (1) {
		int index;
		if (GPIOA->IDR[0] & (0x01)) {
			if (wait_counter % 3 == 0) {
				GPIOB->ODR[0] &= ~(0x01 << 7);
				GPIOC->ODR[0] &= ~(0x01 << 7);
				GPIOA->ODR[0] |= (0x01 << 9); //open red

				__asm volatile("MOV R12, %0" : :"r"(wait_counter));
				__asm volatile("ADDS R12, #0x01");
				__asm volatile("MOV %0, R12" : "=r"(wait_counter));
				for (index = 0; index < wait_milisecond * 333; index++);
			} else if (wait_counter % 3 == 1) {
				GPIOA->ODR[0] &= ~(0x01 << 9);
				GPIOC->ODR[0] &= ~(0x01 << 7);
				GPIOB->ODR[0] |= (0x01 << 7); //open blue

				__asm volatile("MOV R12, %0" : :"r"(wait_counter));
				__asm volatile("ADDS R12, #0x01");
				__asm volatile("MOV %0, R12" : "=r"(wait_counter));
				for (index = 0; index < wait_milisecond * 333; index++);
			} else if (wait_counter % 3 == 2) {
				GPIOA->ODR[0] &= ~(0x01 << 9);
				GPIOB->ODR[0] &= ~(0x01 << 7);
				GPIOC->ODR[0] |= (0x01 << 7); //open green

				__asm volatile("MOV R12, %0" : :"r"(wait_counter));
				__asm volatile("ADDS R12, #0x01");
				__asm volatile("MOV %0, R12" : "=r"(wait_counter));
				for (index = 0; index < wait_milisecond * 333; index++);
			}

		}

	}

}
