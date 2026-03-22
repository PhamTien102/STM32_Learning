/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include <stdio.h>
#include "i2c_lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
uint16_t SUM, RH, TEMP;
uint8_t bits[40];
uint8_t data[5] = {0};
int humidity;
int temperature;
I2C_LCD_HandleTypeDef lcd1;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
char time_buffer[16];
char date_buffer[16];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void delay_us (uint16_t us);
void set_pin_output (GPIO_TypeDef *GPIOx, uint16_t Pin);
void set_pin_input (GPIO_TypeDef *GPIOx, uint16_t Pin);
//void DHT11_Start (GPIO_TypeDef *GPIOx, uint16_t Pin);
uint8_t DHT11_Start (GPIO_TypeDef *GPIOx, uint16_t Pin);
uint8_t DHT11_Response(GPIO_TypeDef *GPIOx, uint16_t Pin);
uint8_t DHT11_Read (GPIO_TypeDef *GPIOx, uint16_t Pin);
void DHT11_Read_40bits(GPIO_TypeDef *GPIOx, uint16_t Pin);
void DHT11_Bits_To_Bytes();
void convert_to_real_data(uint8_t data[]);
void init_lcd(void);
void Buzzer(GPIO_TypeDef *GPIOx, uint16_t Pin,uint16_t ms);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim2); // Kích hoạt Timer 2 ở chế độ đếm cơ bản
  // Khởi tạo lcd
  init_lcd();
  lcd_clear(&lcd1);
  char lcd_buffer[20];

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	if(DHT11_Start(GPIOA,GPIO_PIN_11))
	{
		__disable_irq();
		DHT11_Read_40bits(GPIOA,GPIO_PIN_11);
		__enable_irq();
		DHT11_Bits_To_Bytes();
		convert_to_real_data(data);
		sprintf(lcd_buffer, "Temperature: %d%cC   ", temperature,0xDF);
		lcd_gotoxy(&lcd1,0, 0);      // Nhảy về dòng 0, cột 0
		lcd_puts(&lcd1,lcd_buffer);
		sprintf(lcd_buffer, "Humidity: %.d%%    ", humidity);
		lcd_gotoxy(&lcd1,0, 1);      // Nhảy về dòng 1, cột 0
		lcd_puts(&lcd1,lcd_buffer);

		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		/* 2. Hiển thị Ngày tháng lên dòng 0 */
		// Định dạng: Ngày/Tháng/Năm
		sprintf(date_buffer, "Date: %02d/%02d/%02d", sDate.Date, sDate.Month, sDate.Year);
		lcd_gotoxy(&lcd1,0, 2);      // Nhảy về dòng 2, cột 0
		lcd_puts(&lcd1,date_buffer);

		/* 3. Hiển thị Giờ phút giây lên dòng 1 */
		// Định dạng: Giờ:Phút:Giây
		sprintf(time_buffer, "Time: %02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
		lcd_gotoxy(&lcd1,0, 3);      // Nhảy về dòng 3, cột 0
		lcd_puts(&lcd1,time_buffer);

		/* Buzzer temperature > 30 || humidity < 80 */
		if (temperature > 30 || humidity < 65)
		{
			Buzzer(GPIOA, GPIO_PIN_12, 100);
		}
	}

	HAL_Delay(1000); // đọc 1 giây 1 lần
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

// Delay Micro giây (µs)
void delay_us (uint16_t us)
{
  __HAL_TIM_SET_COUNTER(&htim2, 0);  // Reset counter về 0
  while (__HAL_TIM_GET_COUNTER(&htim2) < us);  // Đợi cho đến khi đạt số us
}

//
void set_pin_output (GPIO_TypeDef *GPIOx, uint16_t Pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void set_pin_input (GPIO_TypeDef *GPIOx, uint16_t Pin)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

//đọc dữ liệu DHT11

uint8_t DHT11_Start(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
	uint8_t response = 0;
	uint16_t timeout = 0;
  set_pin_output(GPIOx, Pin);  // Set PA1 là Output
  HAL_GPIO_WritePin (GPIOx, Pin, 0);   // Kéo xuống 0
  HAL_Delay (20);   // Đợi 18ms theo datasheet
  HAL_GPIO_WritePin (GPIOx, Pin, 1);   // Kéo lên 1
  delay_us (20);    // Đợi 30us
  set_pin_input(GPIOx, Pin);    // Chuyển sang Input để nhận phản hồi

  while (!(HAL_GPIO_ReadPin (GPIOx, Pin)) && timeout < 100) {
  		timeout++;
  		delay_us(1);
  	}
//  if(!(HAL_GPIO_ReadPin(GPIOx, Pin)))
//  {
//	  delay_us(80);
	timeout=0;
	while ((HAL_GPIO_ReadPin (GPIOx, Pin)) && timeout < 100) {
		timeout++;
		delay_us(1);
	}
	if(!HAL_GPIO_ReadPin(GPIOx, Pin))
		response = 1;
//		else
//			response = 0;
//  }

  //    while(HAL_GPIO_ReadPin(GPIOx, Pin));  // đợi xuống LOW
//  timeout=0;
//  while ((HAL_GPIO_ReadPin (GPIOx, Pin)) && timeout < 100) {
//	  timeout++;
//	  delay_us(1);
//	}

  return response;

}

uint8_t DHT11_Response(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    uint8_t response = 0;
    uint16_t timeout = 0;
//    while (HAL_GPIO_ReadPin (GPIOx, Pin) && timeout < 50) {
//        timeout++;
//        delay_us(1);
//      }
//    delay_us(40);
//    while(HAL_GPIO_ReadPin(GPIOx, Pin) && timeout < 100)  // đợi xuống LOW
//    {
//    	timeout++;
//    	delay_us(1);
//    }
//    timeout = 0;
//    while(!(HAL_GPIO_ReadPin(GPIOx, Pin))&& timeout < 100) // đợi HIGH
//    {
//    	timeout++;
//		delay_us(1);
//    }
    if(!(HAL_GPIO_ReadPin(GPIOx, Pin)))
    {
        delay_us(80);
//    	timeout=0;
//    	while (!(HAL_GPIO_ReadPin (GPIOx, Pin)) && timeout < 80) {
//			timeout++;
//			delay_us(1);
//		}
		if(HAL_GPIO_ReadPin(GPIOx, Pin))
			response = 1;
//		else
//			response = 0;
    }

//    while(HAL_GPIO_ReadPin(GPIOx, Pin));  // đợi xuống LOW
    timeout=0;
    while ((HAL_GPIO_ReadPin (GPIOx, Pin)) && timeout < 100) {
        timeout++;
        delay_us(1);
      }

    return response;
}

uint8_t DHT11_Read (GPIO_TypeDef *GPIOx, uint16_t Pin)
{
  uint8_t i = 0, j;
  uint16_t timeout = 0;
  for (j=0; j<8; j++)
  {
//    while (!(HAL_GPIO_ReadPin (GPIOx, Pin)));   // Đợi chân lên 1
	timeout = 0;
	while(!(HAL_GPIO_ReadPin(GPIOx, Pin)) && timeout < 100)
	{
	  timeout++;
	  delay_us(1);
	}
    delay_us (35);   // Đợi 40us
    if (!(HAL_GPIO_ReadPin (GPIOx, Pin)))   // Nếu sau 40us vẫn là 0 -> bit 0
    {
      i &= ~(1<<(7-j));
    }
    else i |= (1<<(7-j));  // Nếu là 1 -> bit 1
//    while ((HAL_GPIO_ReadPin (GPIOx, Pin)));  // Đợi chân xuống 0 lại
    timeout = 0;
    while((HAL_GPIO_ReadPin(GPIOx, Pin)) && timeout < 100)
    {
        timeout++;
        delay_us(1);
    }
  }
  return i;
}

//
void DHT11_Read_40bits(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
    uint16_t timeout;

    for(int i = 0; i < 40; i++)
    {
        // đợi HIGH (bắt đầu bit)
        timeout = 0;
        while(!HAL_GPIO_ReadPin(GPIOx, Pin) && timeout < 100)
        {
            timeout++;
            delay_us(1);
        }

        delay_us(32);  // đọc giữa xung

        if(HAL_GPIO_ReadPin(GPIOx, Pin))
            bits[i] = 1;
        else
            bits[i] = 0;

        // đợi LOW (kết thúc bit)
        timeout = 0;
        while(HAL_GPIO_ReadPin(GPIOx, Pin) && timeout < 100)
        {
            timeout++;
            delay_us(1);
        }
    }
}

void DHT11_Bits_To_Bytes()
{
    for(int i = 0; i < 5; i++)
    {
        data[i] = 0;
        for(int j = 0; j < 8; j++)
        {
            data[i] <<= 1;
            data[i] |= bits[i*8 + j];
        }
    }
}

//
void convert_to_real_data(uint8_t bits[])
{
	if(bits[1]&0X80)	//negative temperature
	{
		humidity = 0-(bits[0]*10+((bits[1]&0x7F)));
	}
	else   //positive temperature
	{
		humidity = bits[0]*10+bits[1];
	}
	if(bits[3]&0X80)	//negative temperature
	{
		temperature = 0-(bits[2]*10+((bits[3]&0x7F)));
	}
	else   //positive temperature
	{
		temperature = bits[2]*10+bits[3];
	}
	//temperature range：-20℃~60℃，humidity range:5％RH~95％RH
	if(humidity>950)
	{
	  humidity=950;
	}
	if(humidity<50)
	{
		humidity=50;
	}
	if(temperature>600)
	{
	  temperature=600;
	}
	if(temperature<-200)
	{
		temperature = -200;
	}
	temperature = temperature/10;//convert to the real temperature value
	humidity = humidity/10; //convert to the real humidity value
}

//
void init_lcd(void) {
    lcd1.hi2c = &hi2c1;     // hi2c1 is your I2C handler
    lcd1.address = 0x4E;    // I2C address for the first LCD
    lcd_init(&lcd1);        // Initialize the first LCD
}

//
void Buzzer(GPIO_TypeDef *GPIOx, uint16_t Pin, uint16_t ms)
{
	HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_SET);   // Bật còi
	HAL_Delay(ms);                                  // Kêu trong bao lâu
	HAL_GPIO_WritePin(GPIOx, Pin, GPIO_PIN_RESET); // Tắt còi
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
