/**
  ******************************************************************************
  * @file     : pot.c
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 23, 2025
  * @brief    : Driver for managing potentiometer measurements.
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "pot.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
uint16_t POT_GetReg(ADC_HandleTypeDef *hadc)
{
	uint16_t Reg;
	HAL_ADC_Start(hadc);
	if(HAL_ADC_PollForConversion(hadc, ADC3_TIMEOUT) == HAL_OK)
	{
		Reg = ADC_REG2MAP(HAL_ADC_GetValue(hadc));
	}
	return Reg;
}


