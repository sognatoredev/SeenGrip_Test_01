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
uint8_t UART2_Startpacket = 0x23;
uint8_t UART3_Startpacket = 0x24;


#define debug_buf_size 1000

static uint8_t debug_buf[debug_buf_size][2];
static uint8_t cnt1, cnt2;
static int seq;
static bool flag_end;

void debug_buf_init(void)
{
	seq = 0;
	cnt1 = 0;
	cnt2 = 0;
	flag_end = false;	
}

void debug_buf_write(int8_t ch, uint8_t data)
{
	uint8_t head;

	if(ch==1){
		head = 0x80+(cnt1&0x7F);
		// head = 0x80;
		cnt1 = cnt1 + 1;			
	}
	else{
        head= (cnt2&0x7F);
		// head = 0x82;
		cnt2 = cnt2 + 1;			
	}

	__disable_irq();
	if(seq<debug_buf_size){
		debug_buf[seq][0] = head;
		debug_buf[seq][1] = data;
		// seq += seq;
		seq++;
	}
	else{
		flag_end = true;
	}	
	__enable_irq();
}


bool debug_buf_read(void)
{
	int8_t buf[4];
	if(flag_end)
    {
		for(int i=0;i<debug_buf_size;++i){
			printf("%02X%02X\r\n",debug_buf[i][0],debug_buf[i][1]);
		}
        seq = 0;		
	}
	return flag_end;
}

#if 1
void UART_RX_Proc (void)
{
    uint32_t i,j,k = 0;

    #if 1
    // if (uart2_rx_flag != 0)
    if (uart2_rx_flag == 0)
    {
        uart2_rx_flag = 0;

        // for (i = 0; i < UART_RXDATA_MAX; i++)
        // {
        //     debug_buf_write(1, uart2_rx_buf[i]);
        // }

        if (debug_buf_read())
        {
            flag_end = false;

        }
        // for ( i = 0; i < (UART_RXDATA_MAX / 16); i++ )
        // {
        //     printf("%02X", UART2_Startpacket);
            
        //     for(j = 0; j < 16; j++)
        //     {
        //         printf("%02X", uart2_rx_buf[j]);
        //     }
        //     // HAL_Delay(1);
        //     // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
        //     // HAL_Delay(1);
        // }
        // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf, UART_RXDATA_MAX, 1000);
        //HAL_Delay(1);
        //     HAL_Delay(1);

        // printf("UART2 RX Complete. print Data.");
        // HAL_Delay(1);
        // printf("\r\nrx callback cnt = %d\r\n", uart2_rxcpltcallback_cnt);
        
        // __HAL_DMA_DISABLE(&hdma_usart2_rx);
        // hdma_usart2_rx.Instance->NDTR = UART_RXDATA_MAX;
        // __HAL_DMA_ENABLE(&hdma_usart2_rx);

        
    }
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
}
    #endif
//     else if (uart3_rx_flag != 0)
//     {
//         uart3_rx_flag = 0;

//         for ( i = 0; i < (UART_RXDATA_MAX / 16); i++ )
//         {
//             printf("%02X", UART3_Startpacket);
            
//             for(j = 0; j < 16; j++)
//             {
//                 printf("%02X", uart3_rx_buf[j]);
//             }
//             // HAL_Delay(1);
//             // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
//             // HAL_Delay(1);
//         }

//         __HAL_DMA_DISABLE(&hdma_usart3_rx);
//         hdma_usart3_rx.Instance->NDTR = UART_RXDATA_MAX;
//         __HAL_DMA_ENABLE(&hdma_usart3_rx);
//     }
// }
#else
void UART_RX_Proc (void)
{
    uint32_t i,j,k = 0;

    #if 1
    if (uart2_rx_flag != 0)
    {
        uart2_rx_flag = 0;

        for ( i = 0; i < (UART_RXDATA_MAX / 16); i++ )
        {
            printf("%02X", UART2_Startpacket);
            
            for(j = 0; j < 16; j++)
            {
                printf("%02X", uart2_rx_buf[j]);
            }
            // HAL_Delay(1);
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
    else if (uart3_rx_flag != 0)
    {
        uart3_rx_flag = 0;

        for ( i = 0; i < (UART_RXDATA_MAX / 16); i++ )
        {
            printf("%02X", UART3_Startpacket);
            
            for(j = 0; j < 16; j++)
            {
                printf("%02X", uart3_rx_buf[j]);
            }
            // HAL_Delay(1);
            // HAL_UART_Transmit(&huart3, (uint8_t *) uart2_rx_buf[])
            // HAL_Delay(1);
        }

        __HAL_DMA_DISABLE(&hdma_usart3_rx);
        hdma_usart3_rx.Instance->NDTR = UART_RXDATA_MAX;
        __HAL_DMA_ENABLE(&hdma_usart3_rx);
    }
}
#endif



/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
