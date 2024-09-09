/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    user_gpio_proc.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "user.h"


/*******************************************************************************
 * EXTERNAL REFERENCES             NOTE: only use if not available in header file
 *******************************************************************************/
/*---- function prototypes ---------------------------------------------------*/
/*---- data declarations -----------------------------------------------------*/

/*******************************************************************************
 * PUBLIC DECLARATIONS             Defined here, used elsewhere
 *******************************************************************************/
/*---- context ---------------------------------------------------------------*/
/*---- function prototypes ---------------------------------------------------*/
/*---- data declarations -----------------------------------------------------*/

/* Timer ch 1 count var. */
uint32_t TIM1_CNT_1 = 0;
uint32_t TIM1_CNT_2 = 0;

#define USER_STR_SIZE               1024

uint8_t USB_CdcRxBuffer_FS[CDC_RXDATA_SIZE] = { 0 };
uint8_t USB_CdcTxBuffer_FS[CDC_TXDATA_SIZE] = { 0 };

uint32_t USB_CdcRxBuffer_FS_cnt = 0;

uint8_t User_Str[USER_STR_SIZE] = { 0 };

uint8_t uart1_rx_buffer[UART_RX_BUFFER_MAX_SIZE] = { 0 };
uint8_t uart1_tx_buffer[UART_TX_BUFFER_MAX_SIZE] = { 0 };

uint8_t uart2_rx_buffer[UART_RX_BUFFER_MAX_SIZE] = { 0 };
uint8_t uart2_tx_buffer[UART_TX_BUFFER_MAX_SIZE] = { 0 };

uint16_t Uart_Rx_IdlelineSize = 0;
uint8_t Uart_Rx_IdlelineIT_Flag = 0x00;


/*******************************************************************************
 * PRIVATE DECLARATIONS            Defined here, used elsewhere
 *******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTION DEFINITIONS
 *******************************************************************************/
/* Display Boot Message */
void BootMessagePrint (void)
{
    sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n");
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " Project Name        : %s\r\n", PROJECT_NAME );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - HW VERSION        : %s\r\n", STR_HW_VER );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - FW VERSION        : %s\r\n", STR_FW_VER );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - BUILD TIME        : %s, %s\r\n", __DATE__, __TIME__ );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n" );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
}

/* Display Clcok Source Message */
void GetClockSourcePrint (void)
{
    sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n");
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - SYSTEM Clock Frequency        : %lu MHz\r\n", (HAL_RCC_GetSysClockFreq() /1000000));
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - HCLK Clock   Frequency        : %lu MHz\r\n", (HAL_RCC_GetHCLKFreq() / 1000000));
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - PCLK1 Clock  Frequency        : %lu MHz\r\n", (HAL_RCC_GetPCLK1Freq() / 1000000));
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, " - PCLK2 Clock  Frequency        : %lu MHz\r\n", (HAL_RCC_GetPCLK2Freq() / 1000000));
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

    sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n" );
    User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
}

void User_CDC_Transmit_FS(uint8_t * pdata, uint16_t datalength)
{
    while(CDC_Transmit_FS((uint8_t *) pdata, datalength) == USBD_BUSY);
}

/*******************************************************************************
 * PRIVATE FUNCTION DEFINITIONS
 *******************************************************************************/

