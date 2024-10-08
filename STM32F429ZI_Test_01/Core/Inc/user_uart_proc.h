/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_uart_proc.h
  * @brief   This file contains all the function prototypes for
  *          the user_uart_proc.c file
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_UART_PROC_H__
#define __USER_UART_PROC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "user.h"

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
extern void UART1_RX_Proc (void);
extern uint8_t USB_CDC_Statecheck (void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_USB_PROC_H__ */

