#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/Motor.h"
#include "../Modules/VC.h"
#include "stm32f4xx_ll_tim.h"



// For debugging only (For logic analyzer)
volatile uint32_t tick = 0;
//int volatile tick_ms =10;

int flag=0;
volatile uint32_t fire=0;  
extern int Motor_Current;

volatile int firing_time;

void TMR_Init(void)
{
   // System clock frequency = 16MHz
   // Tick Period = 1ms
   SysTick_Config(12*TMR_TICK_MS*1000);
   TMR_Stop();
}
void TMR_Start(void)
{
   SysTick->CTRL |= (0x03);
}

void TMR_Stop(void)
{
   SysTick->CTRL &= ~(0x03);
}

void SysTick_Handler(void)
{
   // For debugging only (For logic analyzer)

	 //calculate time of firing
		//int value = Motor_Current/18;
	firing_time = Motor_CurrentValue()/18;
	if(firing_time == 0)
	{
		firing_time++;
	}
	if (flag==0)
	{
		SysTick_Config(12*firing_time*1000);
		tick ^= 1;
		VC_Update();
		Motor_Update();	
		flag=1;
		
	}
	else
	{
		SysTick_Config(12*(10-firing_time)*1000);
		fire=1;
		for (int i=0;i<300;i++);
		fire=0;
		flag=0;

	}
	
	
	//passing this value to function to set timer register
	//start timer 
	
   // Do nothing
   // It is made only to wake the cpu up
}

