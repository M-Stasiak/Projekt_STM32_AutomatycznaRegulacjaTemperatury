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
/**
 * @brief Initializes the PWM (Pulse Width Modulation) peripheral.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @note This function sets up the PWM peripheral, configuring the timer and related parameters for PWM signal generation.
 */
void PWM_Init(PWM_HandleTypeDef* hpwm)
{
	PWM_WriteDuty(hpwm, hpwm->Duty);
	HAL_TIM_PWM_Start(hpwm->htim, hpwm->Channel);
}

/**
 * @brief Sets the duty cycle for the PWM signal.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @param duty The duty cycle value to set (0-100).
 * @note This function adjusts the duty cycle of the PWM signal, controlling the signal's high time relative to the total period.
 */
void PWM_WriteDuty(PWM_HandleTypeDef* hpwm, int duty)
{
	if (duty < 0) duty = 0;
	else if (duty > 100) duty = 100;

	hpwm->Duty = duty;
	int COMPARE = (duty * (__HAL_TIM_GET_AUTORELOAD(hpwm->htim)+1)) / 100;
	__HAL_TIM_SET_COMPARE(hpwm->htim, hpwm->Channel, COMPARE);
}

/**
 * @brief Reads the current duty cycle of the PWM signal.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @return The current duty cycle value (0-100).
 * @note This function retrieves the current duty cycle of the PWM signal.
 */
int PWM_ReadDuty(const PWM_HandleTypeDef* hpwm)
{
	return hpwm->Duty;
}

