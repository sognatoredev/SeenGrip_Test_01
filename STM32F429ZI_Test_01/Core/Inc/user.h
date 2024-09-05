/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user.h
  * @brief   This file contains all the function prototypes
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_H__
#define __USER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/*
    GPIO LED Pin Number.

    GPIO_PIN_0
    GPIO_PIN_7
    GPIO_PIN_14

*/

#define LED_RED_PORT        GPIOB
#define LED_GREEN_PORT      GPIOB
#define LED_BLUE_PORT       GPIOB

#define LED_RED_PIN         GPIO_PIN_14
#define LED_GREEN_PIN       GPIO_PIN_0
#define LED_BLUE_PIN        GPIO_PIN_7

#define LED_ALL_PORT        GPIOB
#define LED_ALL_PIN         GPIO_PIN_14 | GPIO_PIN_0 | GPIO_PIN_7

extern uint32_t TIM1_CNT_1;
extern uint32_t TIM1_CNT_2;

extern uint8_t USB_CdcRxBuffer_FS[];
extern uint8_t USB_CdcTxBuffer_FS[];

extern uint8_t User_Str[];

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_GPIO_PROC_H__ */


