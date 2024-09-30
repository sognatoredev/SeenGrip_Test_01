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

static uint8_t last_uart_source = 0; // 1 = uart2, 2 = uart3
uint8_t current_uart_source = 0;
uint8_t continuous_data_flag = 0;

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

#define MAX_MSEQ                1000

uint16_t mseq_cnt;
MSEQ_t mseq[MAX_MSEQ];

#define debug_buf_size 10000

static uint8_t debug_buf[debug_buf_size][2];
static uint8_t cnt1, cnt2;
static uint16_t seq;
static bool flag_end;

void debug_buf_init(void)
{
	seq = 0;
	cnt1 = 0;
	cnt2 = 0;
	flag_end = false;

    mseq_init();
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
        // #ifdef DEBUG
        // HAL_GPIO_TogglePin(UART_TIME_PORT, UART_TX_CPLT_TIME_PIN); // DEBUG
        // #endif

		for(int i=0;i<debug_buf_size;++i){
			printf("%02X%02X\r\n",debug_buf[i][0],debug_buf[i][1]);
		}

        mseq_display();
        
        seq = 0;

        // #ifdef DEBUG
        // HAL_GPIO_TogglePin(UART_TIME_PORT, UART_TX_CPLT_TIME_PIN); // DEBUG
        // #endif
	}

    
	
    return flag_end;
}

void mseq_init (void)
{
    mseq_cnt = 0;
}

void mseq_upload_master (void)
{
    uint16_t seq_cnt = 0;
    seq_cnt = (uint16_t) seq;

    mseq[mseq_cnt].MC = debug_buf[seq_cnt - 1][1];
    mseq[mseq_cnt].CKT = debug_buf[seq_cnt][1];
}

void mseq_upload_device (void)
{
    uint16_t seq_cnt = 0;
    seq_cnt = (uint16_t) seq;

    mseq[mseq_cnt].CKS = debug_buf[seq_cnt - 2][1];

    mseq_cnt++;
}

void mseq_display (void)
{
    uint16_t i = 0;

    for (i = 0; i < mseq_cnt; ++i)
    {
        printf("%d,%d,%d,%d\r\n", i, mseq[i].MC, mseq[i].CKT, mseq[i].CKS);
        // HAL_Delay(1);
    }
}

void detect_continuous_data (void)
{
    if (uart2_rx_ready)
    {
        uart2_rx_ready = 0;
        current_uart_source = 1;
    }
    else if (uart3_rx_ready)
    {
        uart3_rx_ready = 0;
        current_uart_source = 2;
    }

    if (uart_rx_cnt_total > 8 )
    {
        if (current_uart_source != 0 && current_uart_source == last_uart_source)
        {
            if (!continuous_data_flag)
            {
                mseq_upload_device();
                mseq_upload_master();

                continuous_data_flag++;
            }
            else
            {

            }
            
            // if (current_uart_source == 1)
            // {
            //     mseq_upload_master(rxdata);
            // }
            // else if (current_uart_source == 2)
            // {
            //     mseq_upload_device(rxdata);
            // }
        }
        else if (current_uart_source != last_uart_source)
        {
            continuous_data_flag = 0;
        }
        // uart_rx_cnt_total = 0;
    }
    last_uart_source = current_uart_source;
}

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

            memset(debug_buf, 0, sizeof(debug_buf));
        }
        
    }
    return !buttonstatus;
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

            HAL_UART_DMAStop(&huart2);
            HAL_UART_DMAStop(&huart3);
        }

        if(UserButton_BufferClear() == HAL_OK)
        {
            printf("\r\nUART RX Buffer Clear.\r\n\n");
            
            seq = 0;
            uart_rx_cnt_total = 0;

            HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
            HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
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
