/**
  ******************************************************************************
  * @file     : pid.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : PID controller functions
  *
  ******************************************************************************
  */

#ifndef INC_PID_H_
#define INC_PID_H_

/* Public includes -----------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/
typedef struct {
	float SetPoint, y, u;
	float sumError, lastError;
	float Kp, Ki, Kd;
	float anti_windup_upperLimit, anti_windup_lowerLimit;
	unsigned long long lastTime;
} PID_HandleTypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#define PID_INIT_HANDLE(KP, KI, KD, SETPOINT, ANTIWINDUP_UPPERLIMIT, ANTIWINDUP_LOWERLIMIT) \
  {                                                                                         \
    .Kp = KP,                                                                               \
	.Ki = KI,                                                                               \
	.Kd = KD,                                                                               \
	.SetPoint = SETPOINT,                                                                   \
	.anti_windup_upperLimit = ANTIWINDUP_UPPERLIMIT,                                        \
    .anti_windup_lowerLimit = ANTIWINDUP_LOWERLIMIT                                         \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
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
void PID_Init(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd, float SetPoint, float anti_windup_upperLimit, float anti_windup_lowerLimit);

/**
 * @brief Resets the PID controller's internal state (e.g., integral and derivative terms).
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @note This function clears the accumulated error, integral, and derivative terms in the PID controller.
 */
void PID_Reset(PID_HandleTypeDef* hpid);

/**
 * @brief Sets the PID controller's tuning parameters.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param Kp Proportional gain constant.
 * @param Ki Integral gain constant.
 * @param Kd Derivative gain constant.
 * @note This function allows updating the PID tuning parameters (Kp, Ki, Kd) during operation.
 */
void PID_SetTunings(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd);

/**
 * @brief Sets the reference (setpoint) value for the PID controller.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param SetPoint The desired target value for the PID controller.
 * @note This function updates the desired target value (setpoint) that the PID controller tries to achieve.
 */
void PID_SetReference(PID_HandleTypeDef* hpid, float SetPoint);

/**
 * @brief Calculates the new control output based on the current error.
 * @param hpid Pointer to the PID_HandleTypeDef structure that holds the PID controller state.
 * @param y The current process variable (measured value) to compare with the setpoint.
 * @return The control output that the PID controller generates.
 * @note This function computes the PID control output based on the current error between the setpoint and the measured value (y).
 */
float PID_Calculate(PID_HandleTypeDef* hpid, float y);



#endif /* INC_PID_H_ */
