/*
 *******************************************************************************
 * @file    gpio_driver.h
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
#define PERIPH_BASE           0x40000000UL /*!< Peripheral base address in the alias region */
/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000UL)
#define AFIO_BASE             (APB2PERIPH_BASE + 0x00000000UL)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x00000400UL)

// Địa chỉ gốc của NVIC
#define NVIC_BASE          (0xE000E100UL)

// Thanh ghi ISER (Interrupt Set-Enable): Để bật ngắt
// ISER[0] quản lý từ ngắt 0 đến 31
#define NVIC_ISER0         (*(volatile uint32_t *)(NVIC_BASE + 0x000))

// Thanh ghi IPR (Interrupt Priority): Để đặt mức ưu tiên
// Mỗi thanh ghi 32-bit chứa mức ưu tiên cho 4 ngắt (mỗi ngắt 8-bit)
#define NVIC_IPR_BASE      (NVIC_BASE + 0x300)

/*===============================================================================
 * 								GPIO FUNCTION
 *=============================================================================*/
void GPIO_Init();
void Delay_ms(uint32_t time);

/*===============================================================================
 * 						Init structure definition
 *=============================================================================*/
/*
 * RCC Register
 */
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

/*
 * GPIO Register
 */
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

/*
 * EXTI Register
 */
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
}EXTI_TypeDef;

/*
 * AFIO Register
 */
typedef struct
{
	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR[4];
	volatile uint32_t AFIO_MAPR2;
}AFIO_TypeDef;

/*
 * NVIC Register
 */
typedef struct {
    volatile uint32_t ISER[8];      // 0x000: Interrupt Set-Enable (Bật ngắt)
             uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];      // 0x080: Interrupt Clear-Enable (Tắt ngắt)
             uint32_t R_0[24];
    volatile uint32_t ISPR[8];      // 0x100: Interrupt Set-Pending (Tạo ngắt mềm)
             uint32_t R_1[24];
    volatile uint32_t ICPR[8];      // 0x180: Interrupt Clear-Pending (Xóa hàng chờ)
             uint32_t R_2[24];
    volatile uint32_t IABR[8];      // 0x200: Interrupt Active Bit (Kiểm tra ngắt đang chạy)
             uint32_t R_3[56];
    volatile uint8_t  IPR[240];      // 0x400: Interrupt Priority (Mức ưu tiên - 8 bit mỗi ngắt)
             uint32_t R_4[644];
    volatile uint32_t STIR;         // 0xF00: Software Trigger Interrupt (Kích hoạt nhanh)
} NVIC_TypeDef;


/*===============================================================================
 * 								Variable
 *=============================================================================*/
extern RCC_TypeDef *RCC;
extern GPIO_TypeDef *GPIOA;
extern GPIO_TypeDef *GPIOB;
extern GPIO_TypeDef *GPIOC;
extern GPIO_TypeDef *GPIOD;
extern AFIO_TypeDef *AFIO;
extern EXTI_TypeDef *EXTI;
extern NVIC_TypeDef *NVIC;

#endif /* GPIO_LIB_H_ */
