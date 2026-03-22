/*
 * exti_driver.c
 *
 *  Created on: Mar 12, 2026
 */

#include "exti_driver.h"

void EXTI_Init(EXTI_Mode mode,uint16_t line,EXTI_Trigger trigger,EXTI_GPIOX gpiox)
{
	// enable AFIO Clock - bit 0
	RCC->RCC_APB2ENR |= 0x01;
	// Pin index (1-15)
	uint8_t pin_pos = 0;
	while(!(line & (1<<pin_pos))) pin_pos++;
	// config AFIO_EXTICR[x]
	uint8_t cr_idx = pin_pos/4;
	uint8_t cr_idx_idx = (pin_pos%4) * 4;
	//
	AFIO->AFIO_EXTICR[cr_idx] &= ~(0xF<<cr_idx_idx);
	AFIO->AFIO_EXTICR[cr_idx] |=(gpiox<<cr_idx_idx);
	// enable interrupt mask
	EXTI->EXTI_IMR |= (1<<pin_pos);
	// trigger
	EXTI->EXTI_FTSR &= ~(1<<pin_pos);
	EXTI->EXTI_RTSR &= ~(1<<pin_pos);
	if (trigger == EXTI_TRIGGER_RISING || trigger == EXTI_TRIGGER_RISING_FALLING) EXTI->EXTI_RTSR |= (1<<pin_pos);
	if (trigger == EXTI_TRIGGER_FALLING || trigger == EXTI_TRIGGER_RISING_FALLING) EXTI->EXTI_FTSR |= (1<<pin_pos);
	//
//	NVIC->IPR[pin_pos] = 0x00<<4;
//	NVIC->ISER[0] |= (1<<pin_pos);

	uint8_t irq;

	if(pin_pos <= 4)
	    irq = pin_pos + 6;
	else if(pin_pos <= 9)
	    irq = 23;
	else
	    irq = 40;

	NVIC->IPR[irq] = 0x00<<4;
	NVIC->ISER[irq/32] |= (1<<(irq%32));

}
