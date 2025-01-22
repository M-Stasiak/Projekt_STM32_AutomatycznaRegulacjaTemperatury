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
void PID_Init(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd, float SetPoint, float anti_windup_upperLimit, float anti_windup_lowerLimit);
void PID_Reset(PID_HandleTypeDef* hpid);
void PID_SetTunings(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd);
void PID_SetReference(PID_HandleTypeDef* hpid, float SetPoint);
float PID_Calculate(PID_HandleTypeDef* hpid, float y);


#endif /* INC_PID_H_ */
