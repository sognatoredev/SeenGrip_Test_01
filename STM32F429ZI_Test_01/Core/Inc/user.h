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
#include <stdio.h>
#include <string.h>
#include "usbd_def.h"
/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#ifndef DEBUG
#define DEBUG
#endif
#ifdef DEBUG
#define CONCAT_3(p1, p2, p3)  CONCAT_3_(p1, p2, p3)
/** Auxiliary macro used by @ref CONCAT_3 */
#define CONCAT_3_(p1, p2, p3) p1##p2##p3

#define STRINGIFY_(val) #val
/** Converts a macro argument into a character constant.*/
#define STRINGIFY(val)  STRINGIFY_(val)

/* FW and Board Information */
#define PROJECT_NAME                "STM32F429ZI TEST"

/* board revision */
#define BD_VER_MAJOR                0
#define BD_VER_MINOR                1
/* firmware version */
#define FW_VER_MAJOR                0
#define FW_VER_MINOR                1

/* board revision */
#define HW_BD_REV_01    ( ( 0 << 4 ) | ( 1 ) )
#define STR_BD_VER      "v" STRINGIFY( BD_VER_MAJOR ) "." STRINGIFY( BD_VER_MINOR )
#define DEF_BD_VER      CONCAT_3( HW_BD_REV_01, BD_VER_MAJOR, BD_VER_MINOR )
/* firmware version */
#define STR_FW_VER                      "v" STRINGIFY( FW_VER_MAJOR ) "." STRINGIFY( FW_VER_MINOR ) "." STRINGIFY( FW_VER_PATCH )
#define STR_FW_VER_LEN                  6
#define STR_HW_VER                      "v" STRINGIFY( BD_VER_MAJOR ) "." STRINGIFY( BD_VER_MINOR )
#endif

extern void BootMessagePrint (void);
extern void GetClockSourcePrint (void);

extern void User_CDC_Transmit_FS(uint8_t * pdata, uint16_t datalength);

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

extern uint32_t USB_CdcRxBuffer_FS_cnt;
#define USB_CDC_RX_CNT      (USB_CdcRxBuffer_FS_cnt - 2)

extern uint8_t User_Str[];

/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_GPIO_PROC_H__ */


