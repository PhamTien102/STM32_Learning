/*
 *******************************************************************************
 * @file    gpio_lib.c
 * @brief   Header file of GPIO module.
 *******************************************************************************
 *  Created on: Feb 15, 2026
 *
 */

#include "gpio_lib.h"

/*===============================================================================
 * 								Variable
 *=============================================================================*/
RCC_TypeDef *RCC = (RCC_TypeDef *)RCC_ADDRESS;
GPIO_TypeDef *GPIOA = (GPIO_TypeDef *)PORTA_ADDRESS;
GPIO_TypeDef *GPIOB = (GPIO_TypeDef *)PORTB_ADDRESS;
GPIO_TypeDef *GPIOC = (GPIO_TypeDef *)PORTC_ADDRESS;
GPIO_TypeDef *GPIOD = (GPIO_TypeDef *)PORTD_ADDRESS;

void Delay_ms(uint32_t time)
{
	volatile uint32_t time_n = time*12000;
	while(time_n > 0) time_n--;
}
void GPIO_Init()
{
	RCC->RCC_APB2ENR |= 0x10;
	RCC->RCC_APB2ENR |= 0x04;

	GPIOA->GPIO_CRL &= 0xFFFFFFF0;
	GPIOA->GPIO_CRL |= 0x2;

	GPIOC->GPIO_CRH &= 0xFF0FFFFF;
	GPIOC->GPIO_CRH |= 0x200000;
}

