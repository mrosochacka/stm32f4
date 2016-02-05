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
void GPIO_Config(void);
void NVIC_Config(void);
void ADC_Config();
void USART_Config(void);
void USART_puts( volatile char *s);


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
  ADC_Config();
  NVIC_Config();
  USART_Config();


	while (1)
	{ USART_puts("armprogramming.com");

	}

  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
  /* Infinite loop */
  while (1)
  {
  }
}

void GPIO_Config(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_USART1);

	//PC8 - Tx PC9 - Rx
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
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

void NVIC_Config() {
	NVIC_InitTypeDef NVIC_Init_Structure;
	EXTI_InitTypeDef EXTI_Init_Structure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/* Konfiguracja NVIC i wlaczenie obslugi przerwania */
	NVIC_Init_Structure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Init_Structure);

	/* Bedzie generowane przerwanie na zboczu opadajacym na EXTI_Line0 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EXTI_Init_Structure.EXTI_Line = EXTI_Line0;
	EXTI_Init_Structure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_Init_Structure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init_Structure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_Init_Structure);

	NVIC_Init_Structure.NVIC_IRQChannel = ADC_IRQn;
	NVIC_Init_Structure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init_Structure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init_Structure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Init_Structure);

	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void ADC_Config() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitTypeDef ADC_CommonInitStruct;

	ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitTypeDef ADC_Init_Structure;

	ADC_Init_Structure.ADC_ContinuousConvMode = DISABLE;
	ADC_Init_Structure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init_Structure.ADC_NbrOfConversion = 1;
	ADC_Init_Structure.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init_Structure.ADC_ScanConvMode = DISABLE;

	ADC_Init(ADC1, &ADC_Init_Structure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);

	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

	ADC_Cmd(ADC1, ENABLE);

}
void USART_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef  USART_InitStructure;

	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}
void send_char(char c)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, c);
}

void send_string(const char* s)
{
	while (*s)
		send_char(*s++);
}
void USART_puts(volatile char *s){

	while (1) {
			send_string("Hello world!\r\n");
		}
