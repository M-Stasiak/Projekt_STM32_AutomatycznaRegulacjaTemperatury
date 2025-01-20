/**
  ******************************************************************************
  * @file     : pwm.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : Pulse Width Modulation outputs components driver.
  *
  ******************************************************************************
  */

#ifndef INC_PWM_H_
#define INC_PWM_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32h7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
typedef struct {
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	int Duty;
} PWM_HandleTypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#define PWM_INIT_HANDLE(TIMER_HANDLE, CHANNEL) \
  {                                            \
    .htim = TIMER_HANDLE,                     \
    .Channel = CHANNEL,                        \
    .Duty = 0                                  \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void PWM_Init(PWM_HandleTypeDef* hpwm);
void PWM_WriteDuty(PWM_HandleTypeDef* hpwm, int duty);
int PWM_ReadDuty(const PWM_HandleTypeDef* hpwm);

#endif /* INC_PWM_H_ */
