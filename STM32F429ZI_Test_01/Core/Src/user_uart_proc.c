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
    if ( Uart_Rx_IdlelineIT_Flag != NULL )
    // if((__HAL_UART_GET_FLAG(&huart2, UART_FLAG_RXNE)))
    {
        __HAL_DMA_DISABLE(&hdma_usart2_rx);

        hdma_usart2_rx.Instance->NDTR = UART_RX_BUFFER_MAX_SIZE; // rx buff index init

        __HAL_DMA_ENABLE(&hdma_usart2_rx);

        sprintf(USB_CdcTxBuffer_FS, &uart2_rx_buffer);
        User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

        // memset(uart2_rx_buffer, 0, Uart_Rx_IdlelineSize);
        // Uart_Rx_IdlelineSize = 0;
        Uart_Rx_IdlelineIT_Flag = NULL;
    }
}

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
