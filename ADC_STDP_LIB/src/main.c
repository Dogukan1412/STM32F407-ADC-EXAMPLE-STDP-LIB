
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


void Led_Config(void);
void Buton_Config(void);
void ADC_Config(void);
uint16_t Read_Adc();

uint16_t adc_value;

int main(void)
{
	Led_Config();
	Buton_Config();
	ADC_Config();
  while (1)
  {
	  adc_value = Read_Adc();
	  if(adc_value < 256)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	  }
	  else if(adc_value >= 256 && adc_value < 512)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	  }
	  else if(adc_value >= 512 && adc_value < 768)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	  }
	  else if(adc_value >= 768)
	  {
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14);
	  }

  }
}


void Led_Config(void)
{
	GPIO_InitTypeDef Led = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	Led.GPIO_Mode = GPIO_Mode_OUT;
	Led.GPIO_OType = GPIO_OType_PP;
	Led.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	Led.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Led.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &Led);
}


void Buton_Config(void)
{
	GPIO_InitTypeDef Button = {0};

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	Button.GPIO_Mode = GPIO_Mode_AN;
	Button.GPIO_OType = GPIO_OType_PP;
	Button.GPIO_Pin = GPIO_Pin_1;
	Button.GPIO_PuPd = GPIO_PuPd_DOWN;
	Button.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &Button);
}


void ADC_Config(void)
{
	ADC_InitTypeDef adc = {0};
	ADC_CommonInitTypeDef adc_com = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	adc_com.ADC_DMAAccessMode = DISABLE;
	adc_com.ADC_Mode = ADC_Mode_Independent;
	adc_com.ADC_Prescaler = ADC_Prescaler_Div2;
	adc_com.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&adc_com);

	adc.ADC_ContinuousConvMode = ENABLE;
	adc.ADC_DataAlign = ADC_DataAlign_Right;
	adc.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	adc.ADC_Resolution = ADC_Resolution_10b;
	adc.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &adc);
	ADC_Cmd(ADC1, ENABLE);

}


uint16_t Read_Adc()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_112Cycles);    // Configures for the selected ADC regular channel its corresponding rank in the sequencer and its sample time
	ADC_SoftwareStartConv(ADC1);                                                   // starting adc conversion
	while(!(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)));                               // checking Conversion complete
	return ADC_GetConversionValue(ADC1);
}




/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
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
