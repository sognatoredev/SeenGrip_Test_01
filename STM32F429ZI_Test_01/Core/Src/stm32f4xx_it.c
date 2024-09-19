/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "user.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
uint8_t queData[2400] = { 0 };
uint16_t queDataNum = 0;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern uint8_t CDC_Transmit_Is_Busy(void);
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

  /* USER CODE END DMA1_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream5 global interrupt.
  */
void DMA1_Stream5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream5_IRQn 0 */

  /* USER CODE END DMA1_Stream5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Stream5_IRQn 1 */

  /* USER CODE END DMA1_Stream5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USB On The Go FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
  uint16_t num = 0;
  
  if ((num = Q_NumContents(&USB_TX_Q)) > 0 )
  {
    if (CDC_Transmit_Is_Busy() != USBD_BUSY)
    {
      queDataNum += num;

      Q_Read(&USB_TX_Q, (uint8_t *)queData, num);

      CDC_Transmit_FS(queData, num);
    }
  }

  TIM1_CNT_1++;
  TIM1_CNT_2++;
  TIM1_CNT_3++;
}

/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  if (huart->Instance == USART2)
  {
    #if 1
    // if (TIM1_CNT_3 >= 1000)
    // {
    //   TIM1_CNT_3 = 0;
      uart2_rx_flag = 1;

      uart2_rx_index = (UART_RXDATA_MAX - hdma_usart2_rx.Instance->NDTR);
      
      HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
    // }
    #else
      // uart2_rx_flag = 1;

      // uart2_rx_index = (UART_RXDATA_MAX - hdma_usart2_rx.Instance->NDTR);
      
      // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);

    #endif
  }
  else if (huart->Instance == USART3)
  {
    uart3_rx_flag = 1;

    uart3_rx_index = (UART_RXDATA_MAX - hdma_usart3_rx.Instance->NDTR);
    
    HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
  }
    if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE))
  {
    __HAL_UART_CLEAR_OREFLAG(&huart2);
    
    // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
    // HAL_UART_DeInit(&huart2);
    // HAL_UART_Init(&huart2);
    // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
  }
  else if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE))
  {
    __HAL_UART_CLEAR_OREFLAG(&huart3);
    
    // HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
    // HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
  }
  else if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_FE))
  {
    __HAL_UART_CLEAR_FEFLAG(&huart2);
  }
  else if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_FE))
  {
    __HAL_UART_CLEAR_FEFLAG(&huart3);
  }
}

/**
  * @brief  UART error callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE))
  {
    __HAL_UART_CLEAR_OREFLAG(&huart2);
    
    // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
    // HAL_UART_DeInit(&huart2);
    // HAL_UART_Init(&huart2);
    // HAL_UART_Receive_DMA(&huart2, uart2_rx_buf, UART_RXDATA_MAX);
  }
  else if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_ORE))
  {
    __HAL_UART_CLEAR_OREFLAG(&huart3);
    
    // HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
    // HAL_UART_Receive_DMA(&huart3, uart3_rx_buf, UART_RXDATA_MAX);
  }
  else if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_FE))
  {
    __HAL_UART_CLEAR_FEFLAG(&huart2);
  }
  else if (__HAL_UART_GET_FLAG(&huart3, UART_FLAG_FE))
  {
    __HAL_UART_CLEAR_FEFLAG(&huart3);
  }
}

/* USER CODE END 1 */
