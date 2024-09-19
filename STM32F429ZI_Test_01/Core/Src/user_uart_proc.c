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
uint8_t Startpacket = 0x23;

void UART_RX_Proc (void)
{
    uint32_t i,j,k = 0;

    #if 1
    if (uart2_rx_flag != 0)
    {
        uart2_rx_flag = 0;

        for ( i = 0; i < (UART_RXDATA_MAX / 16); i++ )
        {
            printf("%02X", Startpacket);
            
            for(j = 0; j < 16; j++)
            {
                printf("%02X", uart2_rx_buf[j]);
            }
            HAL_Delay(1);
            // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
            // HAL_Delay(1);
        }
        // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf, UART_RXDATA_MAX, 1000);
        //HAL_Delay(1);
        //     HAL_Delay(1);

        // printf("UART2 RX Complete. print Data.");
        // HAL_Delay(1);

        __HAL_DMA_DISABLE(&hdma_usart2_rx);
        hdma_usart2_rx.Instance->NDTR = UART_RXDATA_MAX;
        __HAL_DMA_ENABLE(&hdma_usart2_rx);
    }
    #else
    if (TIM1_CNT_3 >= 500)
    {
        TIM1_CNT_3 = 0;
        uart2_rx_flag = 1;

        if (uart2_rx_flag != 0)
        {
            uart2_rx_flag = 0;

            for ( i = 0; i < UART_RXDATA_MAX; i++ )
            {
                printf("%c", uart2_rx_buf[i]);\
                // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
                // HAL_Delay(1);
            }
            // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf, UART_RXDATA_MAX, 1000);
            //HAL_Delay(1);
            //     HAL_Delay(1);

            printf("UART2 RX Complete. print Data.");
            HAL_Delay(1);

            __HAL_DMA_DISABLE(&hdma_usart2_rx);
            hdma_usart2_rx.Instance->NDTR = UART_RXDATA_MAX;
            __HAL_DMA_ENABLE(&hdma_usart2_rx);
        }

        uart2_rx_index = (UART_RXDATA_MAX - hdma_usart2_rx.Instance->NDTR);
        
        HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
    }

    #endif
//     else if (uart3_rx_flag != NULL)
//     {
//         uart3_rx_flag = 0x00;

//         for ( i = 0; i < UART_RXDATA_MAX; i++ )
//         {
//             printf(">%s", &uart2_rx_buf[i]);
//         }

//         __HAL_DMA_DISABLE(&hdma_usart3_rx);
//         hdma_usart3_rx.Instance->NDTR = UART_RXDATA_MAX;
//         __HAL_DMA_ENABLE(&hdma_usart3_rx);
//     }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
