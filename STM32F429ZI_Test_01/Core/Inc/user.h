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
#include <stdbool.h>

#include "usbd_def.h"
#include "queue.h"

// #include "user_uart_proc.h"
// #include "debug_buf.h"
/* USER CODE END Includes */

extern uint8_t queData[];
extern uint16_t queDataNum;
extern uint8_t USB_TX_Data[];

extern uint8_t TestValue[];

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

#define USER_BUTTON_PORT        GPIOC

#define USER_BUTTON_PIN         GPIO_PIN_13

#define UART_TIME_PORT          GPIOG

#define UART_RX_BUFWR_PIN       GPIO_PIN_5
#define UART_TX_CPLT_TIME_PIN   GPIO_PIN_6

#define IOLINK_WAKEUP_PORT      GPIOG

#define IOLINK_WAKEUP_PIN       GPIO_PIN_8

#define LED_RED_PORT            GPIOB
#define LED_GREEN_PORT          GPIOB
#define LED_BLUE_PORT           GPIOB

#define LED_RED_PIN             GPIO_PIN_14
#define LED_GREEN_PIN           GPIO_PIN_0
#define LED_BLUE_PIN            GPIO_PIN_7

#define LED_ALL_PORT            GPIOB
#define LED_ALL_PIN             GPIO_PIN_14 | GPIO_PIN_0 | GPIO_PIN_7

#define UART_RXDATA_MAX                     1
#define UART_TXDATA_MAX                     1

extern uint32_t TIM1_CNT_1;
extern uint32_t TIM1_CNT_2;
extern uint32_t TIM1_CNT_3;

extern uint8_t USB_CdcRxBuffer_FS[];
extern uint8_t USB_CdcTxBuffer_FS[];

extern uint32_t USB_CdcRxBuffer_FS_cnt;
#define USB_CDC_RX_CNT      (USB_CdcRxBuffer_FS_cnt - 2)

extern uint8_t User_Str[];

extern uint8_t uart2_rx_buf[];
extern uint8_t uart2_tx_buf[];
extern uint8_t uart3_rx_buf[];
extern uint8_t uart3_tx_buf[];

extern uint16_t uart2_rx_index;
extern uint16_t uart2_tx_index;
extern uint16_t uart3_rx_index;
extern uint16_t uart3_tx_index;

extern uint8_t uart2_rx_flag;
extern uint8_t uart3_rx_flag;

extern uint16_t uart2_rxcpltcallback_cnt;

extern uint8_t UserButton_Flag;

extern uint16_t uart_rx_cnt_total;
extern uint16_t uart2_rx_cnt;
extern uint16_t uart3_rx_cnt;

extern uint8_t uart2_rx_ready;
extern uint8_t uart3_rx_ready;
extern uint8_t uart2_rx_tail_1;
extern uint8_t urat3_rx_tail_1;

#define UART_RX_IDLE_BUFSIZE        5000

extern uint8_t uart2_rx_stack_buf[];

extern uint8_t uart2_rx_IDLE_buf[];
extern uint8_t uart3_rx_IDLE_buf[];
extern uint8_t uart6_rx_IDLE_buf[];

extern uint16_t uart_rx_IDLE_TotalCnt;


/* USER CODE END Private defines */


/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_GPIO_PROC_H__ */


