#include "beep.h"
#include "systick.h"

void BEEP_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

  /*!< Configure SPI_FLASH_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
void beep_ok(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	delay_ms(100);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	delay_ms(50);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	delay_ms(100);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
void beep_err(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	delay_ms(250);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	
}
void beep_done(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	delay_ms(100);
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}
