/**
  ******************************************************************************
  * @file     : pid.c
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : PID controller functions
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "pid.h"

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
 * @brief Initializes the PID controller with given parameters.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param Kp Proportional gain constant.
 * @param Ki Integral gain constant.
 * @param Kd Derivative gain constant.
 * @param SetPoint The desired target value for the PID controller.
 * @param anti_windup_upperLimit The upper limit for anti-windup to prevent integral windup.
 * @param anti_windup_lowerLimit The lower limit for anti-windup to prevent integral windup.
 * @note This function sets the initial tuning parameters and anti-windup limits for the PID controller.
 */
void PID_Init(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd, float SetPoint, float anti_windup_upperLimit, float anti_windup_lowerLimit)
{
	PID_SetTunings(hpid, Kp, Ki, Kd);
	PID_SetReference(hpid, SetPoint);
	hpid->anti_windup_upperLimit = anti_windup_upperLimit;
	hpid->anti_windup_lowerLimit = anti_windup_lowerLimit;
}

/**
 * @brief Resets the PID controller's internal state (e.g., integral and derivative terms).
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @note This function clears the accumulated error, integral, and derivative terms in the PID controller.
 */
void PID_Reset(PID_HandleTypeDef* hpid)
{
	hpid->sumError = 0;
	hpid->lastError = 0;
}

/**
 * @brief Sets the PID controller's tuning parameters.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param Kp Proportional gain constant.
 * @param Ki Integral gain constant.
 * @param Kd Derivative gain constant.
 * @note This function allows updating the PID tuning parameters (Kp, Ki, Kd) during operation.
 */
void PID_SetTunings(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd)
{
	hpid->Kp = Kp;
	hpid->Ki = Ki;
	hpid->Kd = Kd;
}

/**
 * @brief Sets the reference (setpoint) value for the PID controller.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param SetPoint The desired target value for the PID controller.
 * @note This function updates the desired target value (setpoint) that the PID controller tries to achieve.
 */
void PID_SetReference(PID_HandleTypeDef* hpid, float SetPoint)
{
	hpid->SetPoint = SetPoint;
}

/**
 * @brief Calculates the new control output based on the current error.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param y The current process variable (measured value) to compare with the setpoint.
 * @return The control output that the PID controller generates.
 * @note This function computes the PID control output based on the current error between the setpoint and the measured value (y).
 */
float PID_Calculate(PID_HandleTypeDef* hpid, float y)
{
	hpid->y = y;
	//float now = millis();
	//float timeChange = (float)(now-hpid->lastTime);
	float timeChange = 1;

	float error = hpid->SetPoint - hpid->y;
	hpid->sumError += (error*timeChange);
	float dErr = (error - hpid->lastError)/timeChange;

	float p_term = hpid->Kp*error;
	float i_term = hpid->Ki*hpid->sumError;
	float d_term = hpid->Kd*dErr;

	if (i_term >= hpid->anti_windup_upperLimit) i_term = hpid->anti_windup_upperLimit;
	else if (i_term <= hpid->anti_windup_lowerLimit) i_term = hpid->anti_windup_lowerLimit;

	hpid->u = p_term + i_term + d_term;

	hpid->lastError = error;
	//hpid->lastTime = now;

	return hpid->u;
}
