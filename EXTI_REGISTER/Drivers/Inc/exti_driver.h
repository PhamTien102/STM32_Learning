/*
 * exti_driver.h
 *
 *  Created on: Mar 12, 2026
 */

#ifndef EXTI_DRIVER_H_
#define EXTI_DRIVER_H_

#include "gpio_driver.h"

typedef struct
{
  uint32_t Line;      /*!< The Exti line to be configured. This parameter
                           can be a value of @ref EXTI_Line */
  uint32_t Mode;      /*!< The Exit Mode to be configured for a core.
                           This parameter can be a combination of @ref EXTI_Mode */
  uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter
                           can be a value of @ref EXTI_Trigger */
  uint32_t GPIOSel;   /*!< The Exti GPIO multiplexer selection to be configured.
                           This parameter is only possible for line 0 to 15. It
                           can be a value of @ref EXTI_GPIOSel */
} EXTI_ConfigTypeDef;

//#define EXTI_LINE_0                         0x00u    /*!< External interrupt line 0 */
//#define EXTI_LINE_1                         0x01u    /*!< External interrupt line 1 */
//#define EXTI_LINE_2                         0x02u    /*!< External interrupt line 2 */
//#define EXTI_LINE_3                         0x03u    /*!< External interrupt line 3 */
//#define EXTI_LINE_4                         0x04u    /*!< External interrupt line 4 */
//#define EXTI_LINE_5                         0x05u    /*!< External interrupt line 5 */
//#define EXTI_LINE_6                         0x06u    /*!< External interrupt line 6 */
//#define EXTI_LINE_7                         0x07u    /*!< External interrupt line 7 */
//#define EXTI_LINE_8                         0x08u    /*!< External interrupt line 8 */
//#define EXTI_LINE_9                         0x09u    /*!< External interrupt line 9 */
//#define EXTI_LINE_10                        0x0Au    /*!< External interrupt line 10 */
//#define EXTI_LINE_11                        0x0Bu    /*!< External interrupt line 11 */
//#define EXTI_LINE_12                        0x0Cu    /*!< External interrupt line 12 */
//#define EXTI_LINE_13                        0x0Du    /*!< External interrupt line 13 */
//#define EXTI_LINE_14                        0x0Eu    /*!< External interrupt line 14 */
//#define EXTI_LINE_15                        0x0Fu    /*!< External interrupt line 15 */
#define EXTI_LINE_0   (1U << 0)
#define EXTI_LINE_1   (1U << 1)
#define EXTI_LINE_2   (1U << 2)
#define EXTI_LINE_3   (1U << 3)
#define EXTI_LINE_4   (1U << 4)
#define EXTI_LINE_5   (1U << 5)
#define EXTI_LINE_6   (1U << 6)
#define EXTI_LINE_7   (1U << 7)
#define EXTI_LINE_8   (1U << 8)
#define EXTI_LINE_9   (1U << 9)
#define EXTI_LINE_10  (1U << 10)
#define EXTI_LINE_11  (1U << 11)
#define EXTI_LINE_12  (1U << 12)
#define EXTI_LINE_13  (1U << 13)
#define EXTI_LINE_14  (1U << 14)
#define EXTI_LINE_15  (1U << 15)
/** @defgroup EXTI_Mode  EXTI Mode
  * @{
  */
typedef enum {
	EXTI_MODE_NONE,
	EXTI_MODE_INTERRUPT,
	EXTI_MODE_EVENT
}EXTI_Mode;

/** @defgroup EXTI_Trigger  EXTI Trigger
  * @{
  */
typedef enum {
	EXTI_TRIGGER_NONE,
	EXTI_TRIGGER_RISING,
	EXTI_TRIGGER_FALLING,
	EXTI_TRIGGER_RISING_FALLING
}EXTI_Trigger;

/** @defgroup EXTI_GPIOSel  EXTI GPIOSel
  * @brief
  * @{
  */
typedef enum {
	EXTI_GPIOA,
	EXTI_GPIOB,
	EXTI_GPIOC,
	EXTI_GPIOD
}EXTI_GPIOX;

/*!< Interrupt Number Definition */
typedef enum
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
 NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
 HardFault_IRQn              = -13,    /*!< 3 Cortex-M3 Hard Fault Interrupt                     */
 MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
 BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
 UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
 SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
 DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
 PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
 SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  STM32 specific Interrupt Numbers *********************************************************/
 WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
 PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
 TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
 RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
 FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
 RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
 EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
 EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
 EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
 EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
 EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
 DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
 DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
 DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
 DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
 DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
 DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
 DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */
 ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
 USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
 USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
 CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
 CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
 EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
 TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
 TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
 TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
 TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
 TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
 TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
 TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
 I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
 I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
 I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
 I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
 SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
 SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
 USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
 USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
 USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
 EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
 RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
 USBWakeUp_IRQn              = 42,     /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
} IRQn_Type;



void EXTI_Init(EXTI_Mode mode,uint16_t line,EXTI_Trigger trigger,EXTI_GPIOX gpiox);
#endif /* EXTI_DRIVER_H_ */

