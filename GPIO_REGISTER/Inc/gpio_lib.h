/*
 *******************************************************************************
 * @file    gpio_lib.h
 * @author  Pham Minh Tien
 * @brief   Header file of GPIO module.
 *******************************************************************************
 *  Created on: Feb 15, 2026
 *
 */

#ifndef GPIO_LIB_H_
#define GPIO_LIB_H_

#include <stdio.h>
#include <stdint.h>

/*===============================================================================
 * 								Definition
 *=============================================================================*/
#define RCC_ADDRESS							0x40021000
#define PORTA_ADDRESS						0x40010800
#define PORTB_ADDRESS						0x40010C00
#define PORTC_ADDRESS						0x40011000
#define PORTD_ADDRESS						0x40011400
#define PORTE_ADDRESS						0x40011800

/*===============================================================================
 * 								GPIO FUNCTION
 *=============================================================================*/
void GPIO_Init();
void Delay_ms(uint32_t time);

/*===============================================================================
 * 						GPIO Init structure definition
 *=============================================================================*/
/* RRC Register  */
typedef struct
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	//volatile uint32_t RCC_AHBSTR;
	//volatile uint32_t RCC_CFGR2;
}RCC_TypeDef;

typedef struct
{
	volatile uint32_t GPIO_CRL;
	volatile uint32_t GPIO_CRH;
	volatile uint32_t GPIO_IDR;
	volatile uint32_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	volatile uint32_t GPIO_BRR;
	volatile uint32_t GPIO_LCKR;
} GPIO_TypeDef;

/*===============================================================================
 * 								Variable
 *=============================================================================*/
extern RCC_TypeDef *RCC;
extern GPIO_TypeDef *GPIOA;
extern GPIO_TypeDef *GPIOB;
extern GPIO_TypeDef *GPIOC;
extern GPIO_TypeDef *GPIOD;

#endif /* GPIO_LIB_H_ */
