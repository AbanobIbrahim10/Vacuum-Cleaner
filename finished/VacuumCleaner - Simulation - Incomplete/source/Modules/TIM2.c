
#include "stm32f411xe.h"
extern int TMR_TICK_MS;
//TIM_HandleTypeDef htim2;

//static int time;
//static int flag = 0;

//void TIM2_GetTime(int Time)
//{
//		time = Time;
//}

////static void MX_TIM2_Init(void)
////{

////  /* USER CODE BEGIN TIM2_Init 0 */

////  /* USER CODE END TIM2_Init 0 */

////  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
////  TIM_MasterConfigTypeDef sMasterConfig = {0};

////  /* USER CODE BEGIN TIM2_Init 1 */

////  /* USER CODE END TIM2_Init 1 */
////  htim2.Instance = TIM2;
////  htim2.Init.Prescaler = 720-1;
////  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
////  htim2.Init.Period = time;
////  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
////  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
////  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
////  {
////    Error_Handler();
////  }
////  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
////  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
////  {
////    Error_Handler();
////  }
////  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
////  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
////  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
////  {
////    Error_Handler();
////  }
////  /* USER CODE BEGIN TIM2_Init 2 */

////  /* USER CODE END TIM2_Init 2 */

////}


////void Error_Handler(void)
////{
////  /* USER CODE BEGIN Error_Handler_Debug */
////  /* User can add his own implementation to report the HAL error return state */
////  __disable_irq();
////	if(flag == 0)
////	{
////		LL_GPIO_SetOutputPin(MOTOR_PORT,MOTOR_PIN);
////		flag = 1;
////		time = 10;
////	}
////	else
////	{
////		LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
////		flag = 0;
////	}
////	
////	
////	
////  while (1)
////  {
////  }
////  /* USER CODE END Error_Handler_Debug */
////}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
//{
//    if(flag == 0)
//		{
//			LL_GPIO_SetOutputPin(MOTOR_PORT,MOTOR_PIN);
//			flag = 1;
//		}
//		else
//		{
//			LL_GPIO_ResetOutputPin(MOTOR_PORT,MOTOR_PIN);
//		}
//}
void (*ptrFunc) (void);

void TIM_vidPutFunction(void (*ptrF) (void)) {
	ptrFunc = ptrF;
}



void Tim2_Init(void){
    RCC->APB1ENR |= (1<<0); // Enable clock for TIM2
    TIM2->PSC = 16000-1;    // Set PSC+1 = 160000 
                            
    TIM2->ARR = 0xFFFF;     // Reset at maximum CNT value
    
  //  TIM2->EGR |= (1<<0);    // Reset timer counter registers
    TIM2->CNT = 0;          // Manually reset CNT (needed in TINA)
    TIM2->CR1 |= (1<<0);    // Enable timer, CR1[0] = 1
}

void TIM2_IRQHandler(void){
	
  TIM2->SR &= ~(1<<0);  // Clear UIF update interrupt flag
	ptrFunc();
}

