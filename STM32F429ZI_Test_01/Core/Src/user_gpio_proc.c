/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_gpio_proc.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "user_gpio_proc.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/*
    LED_RED_PORT        GPIOB
    LED_GREEN_PORT      GPIOB
    LED_BLUE_PORT       GPIOB
    LED_RED_PIN         GPIO_PIN_14
    LED_GREEN_PIN       GPIO_PIN_0
    LED_BLUE_PIN        GPIO_PIN_7
*/
static void LED_Proc (void)
{
    if(TIM1_CNT_1 >= 500)
    {
        TIM1_CNT_1 = 0;
        
        HAL_GPIO_TogglePin(LED_ALL_PORT, LED_ALL_PIN);
    }    
}

void GPIO_Proc (void)
{
    LED_Proc();
}
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
