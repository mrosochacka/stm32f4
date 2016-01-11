/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
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

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void TIM_Config();
void GPIO_Config();

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used.
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;
  */

  TIM_Config();
  GPIO_Config();

  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
  /* Infinite loop */
  while (1)
  {
  }
}

void GPIO_Config() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//LED 1,2,3,4
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//button USER
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM_Config() {
	//NVIC config
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//TIM1 config
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_TimeBaseInitTypeDef Tim_InitStructure;
	TIM_OCInitTypeDef Tim_OCInitStructure;

	Tim_InitStructure.TIM_Prescaler = 1680-1;
	Tim_InitStructure.TIM_Period = 10000;
	Tim_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	Tim_InitStructure.TIM_RepetitionCounter = 4;
	Tim_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &Tim_InitStructure);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);

	Tim_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	Tim_OCInitStructure.TIM_OutputState = TIM_OutputNState_Enable;
	Tim_OCInitStructure.TIM_Pulse = 1000;
	Tim_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM1, &Tim_OCInitStructure);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
	TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);

	TIM_Cmd(TIM1, ENABLE);
}
