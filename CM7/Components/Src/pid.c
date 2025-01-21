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
void PID_Init(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd, float SetPoint, float anti_windup_upperLimit, float anti_windup_lowerLimit)
{
	PID_SetTunings(hpid, Kp, Ki, Kd);
	PID_SetReference(hpid, SetPoint);
	hpid->anti_windup_upperLimit = anti_windup_upperLimit;
	hpid->anti_windup_lowerLimit = anti_windup_lowerLimit;
}
void PID_Reset(PID_HandleTypeDef* hpid)
{
	hpid->sumError = 0;
	hpid->lastError = 0;
}
void PID_SetTunings(PID_HandleTypeDef* hpid, float Kp, float Ki, float Kd)
{
	hpid->Kp = Kp;
	hpid->Ki = Ki;
	hpid->Kd = Kd;
}
void PID_SetReference(PID_HandleTypeDef* hpid, float SetPoint)
{
	hpid->SetPoint = SetPoint;
}
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
