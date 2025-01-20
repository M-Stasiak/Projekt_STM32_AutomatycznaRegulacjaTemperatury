/**
  ******************************************************************************
  * @file     : lm35.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : Driver for handling the LM35 temperature sensor.
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "lm35.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
float LM35_VOLTAGE2TEMP(float voltage) { return voltage / 10; }
/* Public functions ----------------------------------------------------------*/
float LM35_GetTemp(ADC_HandleTypeDef *hadc)
{
	float LM35_voltage;
	float LM35_temperature;
	HAL_ADC_Start(hadc);
	if(HAL_ADC_PollForConversion(hadc, ADC1_TIMEOUT) == HAL_OK)
	{
		LM35_voltage = ADC_REG2VOLTAGE(HAL_ADC_GetValue(hadc));
		LM35_temperature = LM35_VOLTAGE2TEMP(LM35_voltage);
	}
	return LM35_temperature;
}


