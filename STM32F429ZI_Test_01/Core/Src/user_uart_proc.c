/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_uart_proc.c
  * @brief   This file provides code for the configuration
  *          of all used uart process.
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

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;

void UART_RX_Proc (void)
{
    uint32_t i = 0;

    if (uart2_rx_flag != 0)
    {
        uart2_rx_flag = 0;

        // for ( i = 0; i < UART_RXDATA_MAX; i++ )
        // {
        //     // printf(">%s", &uart2_rx_buf[i]);
        //     HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
        //     HAL_Delay(1);
        // }
        HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf, UART_RXDATA_MAX, 1000);
        //HAL_Delay(1);
        //     HAL_Delay(1);

        //printf("UART2 RX Complete. print Data.");
        //HAL_Delay(1);

        __HAL_DMA_DISABLE(&hdma_usart2_rx);
        hdma_usart2_rx.Instance->NDTR = UART_RXDATA_MAX;
        __HAL_DMA_ENABLE(&hdma_usart2_rx);
    }
    else if (uart3_rx_flag != NULL)
    {
        uart3_rx_flag = 0x00;

        for ( i = 0; i < UART_RXDATA_MAX; i++ )
        {
            printf(">%s", &uart2_rx_buf[i]);
        }

        __HAL_DMA_DISABLE(&hdma_usart3_rx);
        hdma_usart3_rx.Instance->NDTR = UART_RXDATA_MAX;
        __HAL_DMA_ENABLE(&hdma_usart3_rx);
    }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
