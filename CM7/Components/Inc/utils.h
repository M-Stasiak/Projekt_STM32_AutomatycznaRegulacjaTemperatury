/**
  ******************************************************************************
  * @file     : utils.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : Utility functions and macros for embedded system development.
  *
  ******************************************************************************
  */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

/* Public includes -----------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/*
 *---------------------------------------
 *   SysTick Timer Delay Macros
 *---------------------------------------
 */

#define SYSTICK_LOAD (SystemCoreClock/1000000U)
#define SYSTICK_DELAY_CALIB (SYSTICK_LOAD >> 1)

#define DELAY_US(us) \
    do { \
         uint32_t start = SysTick->VAL; \
         uint32_t ticks = (us * SYSTICK_LOAD)-SYSTICK_DELAY_CALIB;  \
         while((start - SysTick->VAL) < ticks); \
    } while (0)

#define DELAY_MS(ms) \
    do { \
        for (uint32_t i = 0; i < ms; ++i) { \
            DELAY_US(1000); \
        } \
    } while (0)

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_UTILS_H_ */
