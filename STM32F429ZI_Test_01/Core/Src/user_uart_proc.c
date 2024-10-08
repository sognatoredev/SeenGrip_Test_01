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

extern  MSEQ_t mseq[MAX_MSEQ];

uint16_t mseq_cnt;
MSEQ_t mseq[MAX_MSEQ];

bool flag_end;

void mseq_upload_master (uint16_t size)
{
    uint16_t rxdataSize = 0;

    rxdataSize = size;

    mseq[mseq_cnt].MC = uart2_rx_IDLE_buf[0];
    mseq[mseq_cnt].CKT = uart2_rx_IDLE_buf[1];
}

void mseq_upload_device (uint16_t size)
{
    uint16_t rxdataSize = 0;
    uint16_t cks_offset = 1;

    rxdataSize = size;

    // mseq[mseq_cnt].CKS = uart3_rx_IDLE_buf[rxdataSize - 1];
    mseq[(mseq_cnt + cks_offset)].CKS = uart6_rx_IDLE_buf[rxdataSize - 1];

    mseq_cnt++;
}

void mseq_display (void)
{
    uint16_t i = 0;

    for (i = 0; i < mseq_cnt; ++i)
    {
        // printf("%d,%d,%d,%d\r\n", i, mseq[i].MC, mseq[i].CKT, mseq[i].CKS);
        printf("%d,%d,%d,%d,", i, mseq[i].MC, mseq[i].CKT, mseq[i].CKS);
        Mseq_Display_PacketFrame(i);
        // HAL_Delay(1);
    }
}


void debug_buf_read (void)
{
  if (uart_rx_IDLE_TotalCnt >= MAX_RX_DATA)
  {
    uart_rx_IDLE_TotalCnt = 0;

    mseq_display();
    // Mseq_Display_PacketFrame();

    HAL_UART_DMAStop(&huart2);
    HAL_UART_DMAStop(&huart6);
  }
}

static uint8_t Decode_MC_ReadWrite (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;
    MCdata = (MCdata >> 7) & 0x01;

    switch (MCdata)
    {
        case 0 :
            return 'W';
        case 1 :
            return 'R';
        default :
            printf("Unexpected value\n");
            return 'X';
    }
}

// static uint8_t Decode_MC_CommunicationChannel (uint8_t pData)
// {
//     uint8_t MCdata = 0;

//     MCdata = pData;
//     MCdata = MCdata >> 5;

//     return MCdata & 0x03;
// }

static uint8_t Print_MC_CommunicationChannel (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;
    MCdata = (MCdata >> 5) & 0x03;
    
    switch (MCdata)
    {
        case 0 :
            printf("%s,", CommunicationChannel.MC_Com_Ch_0);
            break;
        case 1 :
            printf("%s,", CommunicationChannel.MC_Com_Ch_1);
            break;
        case 2 :
            printf("%s,", CommunicationChannel.MC_Com_Ch_2);
            break;
        case 3 :
            printf("%s,", CommunicationChannel.MC_Com_Ch_3);
            break;
    }
}

static uint8_t Decode_MC_Address (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;
    
    return MCdata & 0x1F;
}

static uint8_t Decode_CKT_Type (uint8_t Data)
{
    uint8_t MCdata = 0;
    
    MCdata = Data;

    return (MCdata >> 6) & 0x03;
}

static uint8_t Decode_CKT_Checksum (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;

    return MCdata & 0x3F;
}

static uint8_t Decode_CKS_EventFlag (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;

    return (MCdata >> 7) & 0x01;
}

static uint8_t Decode_CKS_PDStatus (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;

    return (MCdata >> 6) & 0x01;
}

static uint8_t Decode_CKS_Checksum (uint8_t Data)
{
    uint8_t MCdata = 0;

    MCdata = Data;

    return MCdata & 0x3F;
}

void Mseq_Display_PacketFrame (uint16_t cnt)
{
    uint16_t i = 0;
    i = cnt;

    printf("%c,",Decode_MC_ReadWrite(mseq[i].MC));
    Print_MC_CommunicationChannel(mseq[i].MC);
    printf("%02X,%d,%02X,%d,%d,%02X\r\n", 
            Decode_MC_Address(mseq[i].MC),
            Decode_CKT_Type(mseq[i].CKT),
            Decode_CKT_Checksum(mseq[i].CKT),
            Decode_CKS_EventFlag(mseq[i].CKS),
            Decode_CKS_PDStatus(mseq[i].CKS),
            Decode_CKS_Checksum(mseq[i].CKS)
            );
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
