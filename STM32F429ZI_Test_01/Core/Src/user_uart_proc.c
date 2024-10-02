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
extern DMA_HandleTypeDef hdma_usart6_rx;

// extern MSEQ_t mseq;

static uint8_t UserButton_BufferClear (void)
{
    uint8_t buttonstatus = 0;

    if (TIM1_CNT_2 >= 100)
    {
        TIM1_CNT_2 = 0;

        if (UserButton_Flag == 1)
        {
            buttonstatus = UserButton_Flag;

            UserButton_Flag = 0;

            memset(uart2_rx_IDLE_buf, 0, UART_RX_IDLE_BUFSIZE);
            memset(uart6_rx_IDLE_buf, 0, UART_RX_IDLE_BUFSIZE);
            // memset(mseq, 0, 1000);
        }
    }
    return !buttonstatus;
}


void UART_RX_BufferClear (void)
{
    if(UserButton_BufferClear() == HAL_OK)
    {
        printf("\r\nUART RX Buffer Clear.\r\n\n");
        
        uart_rx_IDLE_TotalCnt = 0;
        mseq_cnt = 0;
        
        __HAL_DMA_DISABLE(&hdma_usart2_rx);
        hdma_usart2_rx.Instance->NDTR = UART_RX_IDLE_BUFSIZE;
        __HAL_DMA_ENABLE(&hdma_usart2_rx);

        HAL_UARTEx_ReceiveToIdle_DMA(&huart2, (uint8_t *) uart2_rx_IDLE_buf, UART_RX_IDLE_BUFSIZE);
        __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

        __HAL_DMA_DISABLE(&hdma_usart6_rx);
        hdma_usart6_rx.Instance->NDTR = UART_RX_IDLE_BUFSIZE;
        __HAL_DMA_ENABLE(&hdma_usart6_rx);

        HAL_UARTEx_ReceiveToIdle_DMA(&huart6, (uint8_t *)uart6_rx_IDLE_buf, UART_RX_IDLE_BUFSIZE);
        __HAL_DMA_DISABLE_IT(&hdma_usart6_rx, DMA_IT_HT);
        // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
        // HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
    }

}


/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
