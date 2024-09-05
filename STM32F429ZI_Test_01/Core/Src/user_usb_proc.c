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
    if (TIM1_CNT_2 >= 1000)
    {
        TIM1_CNT_2 = 0;

        sprintf(USB_CdcTxBuffer_FS, "USB CDC TEST %d\r\n", count);
        CDC_Transmit_FS(USB_CdcTxBuffer_FS, strlen(USB_CdcTxBuffer_FS));
        
        memset(USB_CdcTxBuffer_FS,0,strlen(USB_CdcTxBuffer_FS));
        
        count++;
    }
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
