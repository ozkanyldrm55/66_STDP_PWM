/* Stm32f407vg kit uzerinde bulunan ledlerden CH4 %25 doluluk oranında yanar CH3 %50 doluluk oraninda 
   CH2 %75 doluluk oraninda CH1 %100 doluluk oraninda yanmaktadir.*/

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct; // PWM icin


void GPIO_Config(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	//MODE AF olarak kullandigimiz icin AF ayarlarini yapmamiz gerekmektedir
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // timer olarak kullanildigi icin AF olarak kullanilmali.
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD , &GPIO_InitStruct);
}

void TIM_Config(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // Timer_Tick_Freq = 84 MHz clock kullaniyoruz.
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 8399;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4 , &TIM_InitStruct);
	TIM_Cmd(TIM4,ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1; //PWM mod1 mod2 muhabbeti , doluluk oranlariyla ilgili
	TIMOC_InitStruct.TIM_OutputState = ENABLE;//cikisi aktif ettik
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
}

int main(void) {
	GPIO_Config();
	TIM_Config();

  while (1) {
	  /* PWM FREKANSI OLUSTURMAK ICIN ASAGIDAKI FORMULLER KULLANILIR
	   * -> periyod = (Timer_Tick_Freq / PWM_Freq)-1
	   * -> Time_Tick_Freq = Timer_CLK /(Prescaler + 1) 
	   * -> PWM_Freq = Timer_Tick_Freq / (periyod + 1)  
	   *
	   *  //pulse oranini hesaplarken
	   *
	   *  pulse = (periyod + 1) * (duty cycl %) - 1
	   *
	   *        = (9999 + 1) * 100/100 -1 = 9999  // 100 de 100 doluluk oraninda hesaplama yaptik
	   */

	  // PD12
	  TIMOC_InitStruct.TIM_Pulse = 9999;
	  TIM_OC1Init(TIM4 , &TIMOC_InitStruct);
	  TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable); //TIM4 -> CH1 ENABLE

	  // PD13
	  TIMOC_InitStruct.TIM_Pulse = 7999;
	  TIM_OC2Init(TIM4 , &TIMOC_InitStruct);
	  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable); //TIM4 -> CH2 ENABLE

	  // PD14
	  TIMOC_InitStruct.TIM_Pulse = 4999;
	  TIM_OC3Init(TIM4 , &TIMOC_InitStruct);
	  TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable); //TIM4 -> CH3 ENABLE

	  // PD15
	  TIMOC_InitStruct.TIM_Pulse = 2499;
	  TIM_OC4Init(TIM4 , &TIMOC_InitStruct);
	  TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable); //TIM4 -> CH4 ENABLE
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
