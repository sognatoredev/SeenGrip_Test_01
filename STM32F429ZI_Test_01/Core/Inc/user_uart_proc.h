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
#include <stdint.h>
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
extern uint16_t mseq_cnt;

typedef struct
{
    uint8_t cnt;
    uint8_t MC;
    uint8_t CKT;
    uint8_t CKS;

    uint8_t rw;
    uint8_t ch;
    uint8_t addr;
    uint8_t type;
    uint8_t ckt_cs;
    uint8_t event;
    uint8_t valid;
    uint8_t cks_cs;
} MSEQ_t;

typedef struct MC_Communication_channel
{
  uint8_t * MC_Com_Ch_0;
  uint8_t * MC_Com_Ch_1;
  uint8_t * MC_Com_Ch_2;
  uint8_t * MC_Com_Ch_3;
} MC_Communication_channel_t;

MC_Communication_channel_t CommunicationChannel = 
{
  .MC_Com_Ch_0 = "Process",
  .MC_Com_Ch_1 = "Page",
  .MC_Com_Ch_2 = "Diagnosis",
  .MC_Com_Ch_3 = "ISDU",
};

#define MAX_RX_DATA             20000

#define MAX_MSEQ                1000
extern  MSEQ_t mseq[MAX_MSEQ];

extern void UART_RX_BufferClear (void);
extern void Mseq_Display_PacketFrame (uint16_t cnt);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ USER_USB_PROC_H__ */

