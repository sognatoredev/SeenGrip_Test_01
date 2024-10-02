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
#ifndef __USER_USB_PROC_H__
#define __USER_USB_PROC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "user.h"
#include "usart.h"

/* USER CODE BEGIN Private defines */
#include <stdbool.h>
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */

extern void debug_buf_init(void);
extern void debug_buf_write(int8_t ch, uint8_t data);
extern bool debug_buf_read(void);


extern void mseq_display (void);
// extern void mseq_upload_master (void);
// extern void mseq_upload_device (void);
extern void mseq_upload_master (uint16_t size);
extern void mseq_upload_device (uint16_t size);
extern void detect_continuous_data (void);

extern void UART_RX_Proc (void);

extern uint16_t mseq_cnt;

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_USB_PROC_H__ */

