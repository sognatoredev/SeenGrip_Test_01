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
#include "user_gpio_proc.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
static uint16_t count = 0;

/* USER CODE BEGIN 1 */
void USB_CDC_Proc (void)
{
    #if 1
    if (TIM1_CNT_2 >= 1000)
    {
        TIM1_CNT_2 = 0;

        sprintf(USB_CdcTxBuffer_FS, "USB CDC TEST %d\r\n", count);
        User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));

        sprintf(USB_CdcTxBuffer_FS, "USB CDC Transmit OK.\r\n");
        User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
        
        memset(USB_CdcTxBuffer_FS, 0, strlen(USB_CdcTxBuffer_FS));
        
        count++;
    }
    #else
    if (TIM1_CNT_2 >= 1000)
    {
        TIM1_CNT_2 = 0;

        sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n");
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));


        sprintf(USB_CdcTxBuffer_FS, " Project Name        : %s\r\n", PROJECT_NAME );
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));


        sprintf(USB_CdcTxBuffer_FS, " - HW VERSION        : %s\r\n", STR_HW_VER );
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));


        sprintf(USB_CdcTxBuffer_FS, " - FW VERSION        : %s\r\n", STR_FW_VER );
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));


        sprintf(USB_CdcTxBuffer_FS, " - BUILD TIME        : %s, %s\r\n", __DATE__, __TIME__ );
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));


        sprintf(USB_CdcTxBuffer_FS, "-------------------------------------------\r\n" );
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
    }
    #endif
}

void USB_CDC_RX_Proc(void)
{
    if (USB_CdcRxBuffer_FS_cnt != NULL)
    {
        if (!strncmp("RXBUF ALL PRINT", USB_CdcRxBuffer_FS, USB_CDC_RX_CNT))
        {
            sprintf(USB_CdcTxBuffer_FS, "USB ALL\r\n");
            User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
        }
        else if (!strncmp("RXBUF CLEAR", USB_CdcRxBuffer_FS, USB_CDC_RX_CNT))
        {
            sprintf(USB_CdcTxBuffer_FS, "USB RX Buffer Clear\r\n");
            User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
        }
        else if (!strncmp("SYSTEM RESET", USB_CdcRxBuffer_FS, USB_CDC_RX_CNT))
        {
            sprintf(USB_CdcTxBuffer_FS, "SYSTEM RESET\r\n");
            User_CDC_Transmit_FS((uint8_t *) USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
            HAL_NVIC_SystemReset();
        }

        memset(USB_CdcRxBuffer_FS, 0, USB_CdcRxBuffer_FS_cnt);
        USB_CdcRxBuffer_FS_cnt = 0;
    }
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
