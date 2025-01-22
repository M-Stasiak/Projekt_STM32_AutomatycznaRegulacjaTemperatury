/**
  ******************************************************************************
  * @file     : i2c_lcd.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 20, 2025
  * @brief    : Driver for handling the LM35 temperature sensor.
  *
  ******************************************************************************
  */

#ifndef INC_I2C_LCD_H_
#define INC_I2C_LCD_H_

//------------------[ Public includes ]-------------------

#ifdef USE_HAL_DRIVER
#include "stm32h7xx_hal.h"
#endif
#include "stdint.h"

//------------------[ Public  typedef ]-------------------

typedef struct {
	I2C_HandleTypeDef *hi2c;
	uint8_t I2C_LCD_Address;
	uint8_t I2C_LCD_nCol;
	uint8_t I2C_LCD_nRow;
	uint8_t DisplayCtrl;
	uint8_t BacklightVal;
} I2C_LCD_HandleTypeDef;

//-------------------[ Public define ]--------------------


//-------------------[ Public macro ]---------------------

#ifdef USE_HAL_DRIVER
#define I2C_LCD_INIT_HANDLE(I2C_HANDLE, ADDRESS, NCOL, NROW) \
  {                                                          \
    .hi2c = I2C_HANDLE,                                      \
    .I2C_LCD_Address = ADDRESS,                              \
    .I2C_LCD_nCol = NCOL,                                    \
	.I2C_LCD_nRow = NROW                                     \
  }
#endif

//-----[ Prototypes For All User External Functions ]-----

void I2C_LCD_Init(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_Clear(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_Home(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_SetCursor(I2C_LCD_HandleTypeDef* hi2c, uint8_t Col, uint8_t Row);
void I2C_LCD_WriteChar(I2C_LCD_HandleTypeDef* hi2c, char Ch);
void I2C_LCD_WriteString(I2C_LCD_HandleTypeDef* hi2c, char* Str);

void I2C_LCD_ShiftLeft(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_ShiftRight(I2C_LCD_HandleTypeDef* hi2c);

void I2C_LCD_Backlight(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_NoBacklight(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_Display(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_NoDisplay(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_Cursor(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_NoCursor(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_Blink(I2C_LCD_HandleTypeDef* hi2c);
void I2C_LCD_NoBlink(I2C_LCD_HandleTypeDef* hi2c);

void I2C_LCD_CreateCustomChar(I2C_LCD_HandleTypeDef* hi2c, uint8_t CharIndex, const uint8_t* CharMap);
void I2C_LCD_PrintCustomChar(I2C_LCD_HandleTypeDef* hi2c, uint8_t CharIndex);

#endif /* INC_I2C_LCD_H_ */
