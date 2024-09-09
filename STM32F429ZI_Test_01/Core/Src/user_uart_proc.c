/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_usb_proc.c
  * @brief   This file provides code for the configuration
  *          of all used usb process.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "user_uart_proc.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/


/* USER CODE BEGIN 1 */
void UART1_RX_Proc (void)
{
    if ( Uart_Rx_IdlelineIT_Flag != 0x00 )
    // if((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE)))
    {
        sprintf(USB_CdcTxBuffer_FS, &uart2_rx_buffer);
        User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

        memset(uart2_rx_buffer, 0, Uart_Rx_IdlelineSize);
        Uart_Rx_IdlelineIT_Flag = 0x00;
    }

    
}

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
