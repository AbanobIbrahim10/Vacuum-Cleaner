#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stdio.h"
#include "stm32f411xe.h"


///Oscilloscope should monitor C6 and C7 channels
//volatile uint32_t fire=0;

//void ISR_TMR2(void){
//    fire ^=1;
//}

int main(void)
{
    /* Initialization */
   
   printf("Vacuum Cleaner is starting ...\n");
   
    SW_Init();
    DISP_Init();
    VC_Init();
    Motor_Init();

    //Initialize the timer and start it
    TMR_Init();
    TMR_Start();
	
//		Tim2_Init();
//TIM2->EGR |= (1<<0);       // Reset timer counter registers
//  TIM2->CNT = 0;             // Manually reset CNT (needed in TINA)
//  TIM2->CR1 |= (1<<0);       // Enable timer
//	TIM_vidPutFunction(ISR_TMR2);
    while (1)
    {
			
      // Sleep
      __WFI();
    }

    return 0;
}

