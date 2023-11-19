#include "../Main/main.h"
#include "../Port/Port.h"
#include "../Modules/Motor.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f411xe.h"
#include "stm32f4xx_ll_tim.h"


volatile int Motor_Current;
volatile int Motor_Target;

int Tick_Count=0;
int Firing_Time=0;
volatile int count = 0;
//volatile int fire=0;
//void ISR_TMR2(void);

void Motor_Init()
{
	LL_GPIO_SetPinOutputType(MOTOR_PORT, MOTOR_PIN, LL_GPIO_OUTPUT_PUSHPULL);
	Motor_Current=170;
	Motor_Target=90;
//	TIM_vidPutFunction(ISR_TMR2);
}

void Motor_SetAngle(int Angle)
{
	Motor_Target = Angle;
}

void Motor_Update(void)
{
	
	//start timer
//	TIM2->EGR |= (1<<0);       // Reset timer counter registers
//  TIM2->CNT = 0;             // Manually reset CNT (needed in TINA)
//  TIM2->CR1 |= (1<<0);       // Enable timer
	
	if(Motor_Target - Motor_Current == 5 || Motor_Current - Motor_Target == 5)//Harmonic mode
	{
		if(Tick_Count >= 1)
		{
				Tick_Count = 0;
				if(Motor_Target > Motor_Current)
				{
					Motor_Current = Motor_Current + 10;
				}
				else
				{
					Motor_Current = Motor_Current - 10;
				}
		}
		else
		{
			Tick_Count ++;
		}
	}
	else // soft switching mode
	{
		if(Tick_Count >= 3)
		{
			Tick_Count=0;
			if(Motor_Target > Motor_Current)
			{
					Motor_Current++;
			}
			else if(Motor_Target < Motor_Current)
			{
					Motor_Current--;
			}
			else
			{
					Motor_Current = Motor_Current + 5;
			}
		}
		else
		{
			Tick_Count++;
		}
	}
}

int Motor_CurrentValue(void)
{
	return Motor_Current;
}
//void ISR_TMR2(void){
//    if (count >= Firing_Time)
//		{
//				fire=1;
//				count++;
//				LL_GPIO_SetOutputPin(MOTOR_PORT,MOTOR_PIN);
//			if (count >= Firing_Time + 10) {  // While CNT is below 100
//				LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
//				fire=0;
//				count= 0;
//				TIM2->CR1 &= ~(1<<0);    // Disable timer, for now
//				
//			}

//		}
//		else
//		{
//			count++;
//		}
//  

//    TIM2->SR &= ~(1<<0);  // Clear UIF update interrupt flag
//}