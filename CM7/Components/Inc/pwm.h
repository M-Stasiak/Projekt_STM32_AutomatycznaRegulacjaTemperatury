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
    .htim = TIMER_HANDLE,                      \
    .Channel = CHANNEL,                        \
    .Duty = 0                                  \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Initializes the PWM (Pulse Width Modulation) peripheral.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @note This function sets up the PWM peripheral, configuring the timer and related parameters for PWM signal generation.
 */
void PWM_Init(PWM_HandleTypeDef* hpwm);

/**
 * @brief Sets the duty cycle for the PWM signal.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @param duty The duty cycle value to set (0-100).
 * @note This function adjusts the duty cycle of the PWM signal, controlling the signal's high time relative to the total period.
 */
void PWM_WriteDuty(PWM_HandleTypeDef* hpwm, int duty);

/**
 * @brief Reads the current duty cycle of the PWM signal.
 * @param hpwm Pointer to the PWM_HandleTypeDef structure containing the PWM configuration.
 * @return The current duty cycle value (0-100).
 * @note This function retrieves the current duty cycle of the PWM signal.
 */
int PWM_ReadDuty(const PWM_HandleTypeDef* hpwm);


#endif /* INC_PWM_H_ */
