/**
  ******************************************************************************
  * @file     : pwm.c
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : Pulse Width Modulation outputs components driver.
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "pwm.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
void PWM_Init(PWM_HandleTypeDef* hpwm)
{
	PWM_WriteDuty(hpwm, hpwm->Duty);
	HAL_TIM_PWM_Start(hpwm->htim, hpwm->Channel);
}

void PWM_WriteDuty(PWM_HandleTypeDef* hpwm, int duty)
{
	if (duty < 0) duty = 0;
	else if (duty > 100) duty = 100;

	hpwm->Duty = duty;
	int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hpwm->htim)+1)) / 100;
	__HAL_TIM_SET_COMPARE(hpwm->htim, hpwm->Channel, COMPARE);
}

int PWM_ReadDuty(const PWM_HandleTypeDef* hpwm)
{
	return hpwm->Duty;
}

