/*******************************
*连线说明：
*1--SS  <----->PA4
*2--SCK <----->PA5
*3--MOSI<----->PA7
*4--MISO<----->PA6
*5--悬空
*6--GND <----->GND
*7--RST <----->PA0
*8--VCC <----->VCC

*--PWM <----->PB0
*--EXIT1 <----->PB1
*--EXIT2 <----->PB2
*--BEEP <----->PB5

************************************/

#include "stm32f10x.h"
#include "bsp_usart1.h"		
#include "SysTick.h"	
#include "rc522.h"	  
#include "spi.h"
#include "pwm_output.h"
//#include "misc.h"
#include "gpio_out.h"
#include "exti_gpio.h"
#include "beep.h"

/**************************************************************/

#define YANGCHENGUANG  0x9da12933
#define WUPENG         0xede72133
#define CHENDUYU       0x4d832033
#define LIUZHIYU       0xf7ab0641
#define WHITECARD      0x7e3da723
#define BLUECARD       0x41cce92b

/**************************************************************/

void opendoor(void);

/**************************************************************/
/*全局变量*/
unsigned char CT[2];//卡类型
unsigned char SN[4]; //卡号
uint32_t sn;
/*函数声明*/

int main(void)
{		
//	u8 x=0;
	unsigned char status;
	u8 Data[16];
	u8 i;
	u8 k=0;//读写错误重试次数
	u8 j;
	
  
	USART1_Config();
	//printf("USART1_Config success\n");
	SysTick_Init();
	
	//printf("SysTick_Init success\n");
	SPI_FLASH_Init();
	//printf("SPI_FLASH_Init success\n");
	InitRc522();				
	//printf("InitRc522 success\n");
	TIM3_PWM_Init();
	//printf("TIM3_PWM_Init success\n");
	GPIO_OUT_Init();
	//NVIC_Configuration();
	EXTI_PB1_Config();
	EXTI_PB2_Config();
	BEEP_Init();
	beep_ok();
	
  	while(1) 
{	
		
			status = PcdRequest(PICC_REQIDL,CT);/*扫描卡*/
			status = PcdAnticoll(SN);/*防冲撞*/
			//printf("%d",status);
			if (status==MI_OK)
			{
				k=0;
				sn=((SN[0]<<24)|(SN[1]<<16)|(SN[2]<<8)|(SN[3]));
				//printf("MI_OK\n");
				//printf("%x\n",sn);
				
				if((sn==YANGCHENGUANG)||(sn==LIUZHIYU)||(sn==CHENDUYU)||(sn==WUPENG)||(sn==BLUECARD))
				{
					//printf("OPEN DOOR\n");
					beep_ok();
					opendoor();
				}
				
			}
			else
			{
				k++;
				if((k++)>20)
				{
					SPI_FLASH_Init();
					//printf("SPI_FLASH_Init success\n");
					Reset_RC522();
					//printf("InitRc522 success\n");
					k=0;
				}
			}
			delay_ms(100);
	}
}

void opendoor(void)
{
	int i;

	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);//开信号时钟PB0
	
	//TIM3_Mode_Config(180);//开门转角
	for(i=0;i<=46;i++)
	{
		TIM3_Mode_Config(180+10*i);
		if(i==0)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_2);//启动舵机电源
			delay_ms(10);
		}
		delay_ms(25);
	}
	beep_done();
	delay_ms(5000);//开门等待
	
	TIM3_Mode_Config(180);//关门转角
	delay_ms(800);//关门等待
	GPIO_SetBits(GPIOA, GPIO_Pin_2);//关舵机电源
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Disable);//关信号时钟PB0
	
	
	

}



