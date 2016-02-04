/**
*****************************************************************************
**
**  File        : stm32f4xx_it.c
**
**  Abstract    : Main Interrupt Service Routines.
**                This file provides template for all exceptions handler and
**                peripherals interrupt service routine.
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed �as is,� without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
void TIM1_CC_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) {
		GPIO_WriteBit(GPIOD, GPIO_Pin_12, 1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_12));
		TIM_SetCompare1(TIM1, TIM_GetCapture1(TIM1)+1000);
		TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
	}

	if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) {   //CC1 - osiagniecie wartosci
    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		ADC1->CR2 |= ADC_CR2_SWSTART;
		while( !(ADC1->SR & ADC_SR_EOC));	//Czekaj na ustwienie flagi EOC
  }
}
void TIM1_UP_TIM10_IRQHandler(void) {
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) {
		GPIO_WriteBit(GPIOD, GPIO_Pin_13, 1-GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_13));
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}

void  EXTI0_IRQHandler(void) {
	uint8_t bitState=GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_12);
	GPIO_WriteBit(GPIOD, GPIO_Pin_12, 1-bitState);
	ADC_SoftwareStartConv(ADC1);
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void ADC_IRQHandler(void) {
	if(ADC_GetITStatus(ADC1, ADC_IT_EOC) != RESET) {
		uint16_t res = ADC_GetConversionValue(ADC1)>>4;
		ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
	}
}

void USART1_IRQHandler(void) {

	static uint16_t RxByte = 0x00;

	if (USART_GetITStatus(USART1, USART_IT_TC) == SET)
	{

		if (USART_GetFlagStatus(USART1, USART_FLAG_TC))
		{
			USART_SendData(USART1, RxByte);
			USART_ITConfig(USART1, USART_IT_TC, DISABLE);
		}

		USART_ClearITPendingBit(USART1, USART_IT_TC);
	}

	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE))
		{
			RxByte = USART_ReceiveData(USART1);
			USART_ITConfig(USART1, USART_IT_TC, ENABLE);
		}

		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}


