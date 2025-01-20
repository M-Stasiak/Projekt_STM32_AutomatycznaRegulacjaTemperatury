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

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
float LM35_VOLTAGE2TEMP(float voltage);
float LM35_GetTemp(ADC_HandleTypeDef *hadc);

#endif /* INC_LM35_H_ */
