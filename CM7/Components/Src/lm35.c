/**
  ******************************************************************************
  * @file     : lm35.c
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

/**
 * @brief Converts the input voltage to temperature based on LM35 sensor characteristics.
 * @param voltage The input voltage measured from the LM35 sensor.
 * @return The corresponding temperature in Celsius.
 * @note The LM35 sensor provides a voltage that is linearly proportional to the temperature in Celsius, with a typical scale factor of 10mV per degree Celsius.
 */
float LM35_VOLTAGE2TEMP(float voltage) { return voltage / 10; }
/* Public functions ----------------------------------------------------------*/

/**
 * @brief Gets the current temperature reading from the LM35 sensor using ADC.
 * @param hadc Pointer to the ADC_HandleTypeDef structure containing ADC configuration.
 * @param hfilter Pointer to the LM35_Filter_HandleTypeDef structure for filtering temperature readings.
 * @return The current temperature in Celsius after applying filtering.
 * @note This function reads the ADC value, converts it to voltage, and then applies a filter to smooth the temperature reading.
 */
float LM35_GetTemp(ADC_HandleTypeDef *hadc, LM35_Filter_HandleTypeDef *hfilter)
{
	float LM35_voltage;
	float LM35_temperature;
	HAL_ADC_Start(hadc);
	if(HAL_ADC_PollForConversion(hadc, ADC1_TIMEOUT) == HAL_OK)
	{
		LM35_voltage = ADC_REG2VOLTAGE(HAL_ADC_GetValue(hadc));
		LM35_temperature = LM35_VOLTAGE2TEMP(LM35_voltage) - 2;
		LM35_temperature = LM35_UpdateFilter(hfilter, LM35_temperature);
	}
	return LM35_temperature;
}

/**
 * @brief Updates the temperature filter with a new value.
 * @param hfilter Pointer to the LM35_Filter_HandleTypeDef structure that holds the filter state.
 * @param new_value The new temperature value to be added to the filter.
 * @return The updated filtered temperature value.
 * @note This function updates the filter state to provide a smoothed temperature value over time, reducing noise from the sensor.
 */
float LM35_UpdateFilter(LM35_Filter_HandleTypeDef *hfilter, float new_value) {
	hfilter->filtered_value = hfilter->alpha * new_value + (1.0f - hfilter->alpha) * hfilter->filtered_value;
    return hfilter->filtered_value;
}


