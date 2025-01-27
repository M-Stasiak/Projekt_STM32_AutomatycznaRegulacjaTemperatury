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

#ifndef INC_LM35_H_
#define INC_LM35_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32h7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
typedef struct {
    float alpha;
    float filtered_value;
} LM35_Filter_HandleTypeDef;

/* Public define -------------------------------------------------------------*/
#define ADC_BIT_RES      16      // [bits]
#define ADC_REG_MAX      (float)((1ul << ADC_BIT_RES) - 1)
#define ADC_VOLTAGE_MAX  3.3f    // [V]
#define ADC1_TIMEOUT     1 		 // [ms]

/* Public macro --------------------------------------------------------------*/

#define __LINEAR_TRANSFORM(x,amin,amax,bmin,bmax) (((x-amin)/(amax-amin))*(bmax-bmin)+bmin)
#define ADC_REG2VOLTAGE(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,         \
                                                       0.0f, ADC_REG_MAX,    \
                                                       0.0f, ADC_VOLTAGE_MAX))

#ifdef USE_HAL_DRIVER
#define LM35_FILTER_INIT_HANDLE(ALPHA) \
  {                                    \
    .alpha = ALPHA,                    \
	.filtered_value = 0.0f			   \
  }
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
 * @brief Converts the input voltage to temperature based on LM35 sensor characteristics.
 * @param voltage The input voltage measured from the LM35 sensor.
 * @return The corresponding temperature in Celsius.
 * @note The LM35 sensor provides a voltage that is linearly proportional to the temperature in Celsius, with a typical scale factor of 10mV per degree Celsius.
 */
float LM35_VOLTAGE2TEMP(float voltage);

/**
 * @brief Gets the current temperature reading from the LM35 sensor using ADC.
 * @param hadc Pointer to the ADC_HandleTypeDef structure containing ADC configuration.
 * @param hfilter Pointer to the LM35_Filter_HandleTypeDef structure for filtering temperature readings.
 * @return The current temperature in Celsius after applying filtering.
 * @note This function reads the ADC value, converts it to voltage, and then applies a filter to smooth the temperature reading.
 */
float LM35_GetTemp(ADC_HandleTypeDef *hadc, LM35_Filter_HandleTypeDef *hfilter);

/**
 * @brief Updates the temperature filter with a new value.
 * @param hfilter Pointer to the LM35_Filter_HandleTypeDef structure that holds the filter state.
 * @param new_value The new temperature value to be added to the filter.
 * @return The updated filtered temperature value.
 * @note This function updates the filter state to provide a smoothed temperature value over time, reducing noise from the sensor.
 */
float LM35_UpdateFilter(LM35_Filter_HandleTypeDef *hfilter, float new_value);

#endif /* INC_LM35_H_ */
