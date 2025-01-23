/**
  ******************************************************************************
  * @file     : pot.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 23, 2025
  * @brief    : Driver for managing potentiometer measurements.
  *
  ******************************************************************************
  */

#ifndef INC_POT_H_
#define INC_POT_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32h7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/


/* Public define -------------------------------------------------------------*/
#define ADC_BIT_RES      16      // [bits]
#define ADC_REG_MAX      (float)((1ul << ADC_BIT_RES) - 1)
#define ADC_MAP_MAX      60.0f    // [V]
#define ADC3_TIMEOUT     1 		 // [ms]

/* Public macro --------------------------------------------------------------*/

#define __LINEAR_TRANSFORM(x,amin,amax,bmin,bmax) (((x-amin)/(amax-amin))*(bmax-bmin)+bmin)
#define ADC_REG2MAP(reg) (1000.0f*__LINEAR_TRANSFORM((float)reg,         \
                                                       0.0f, ADC_REG_MAX,    \
                                                       20.0f, ADC_MAP_MAX))

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
uint16_t POT_GetReg(ADC_HandleTypeDef *hadc);

#endif /* INC_POT_H_ */
