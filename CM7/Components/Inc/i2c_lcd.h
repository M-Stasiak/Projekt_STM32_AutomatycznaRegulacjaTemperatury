/**
  ******************************************************************************
  * @file     : i2c_lcd.h
  * @author   : MS    Mateusz.Stasiak@student.put.poznan.pl
  * @version  : 1.0.0
  * @date     : Jan 21, 2025
  * @brief    : Driver for controlling an I2C-based LCD display.
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

/**
 * @brief Initializes the LCD display using the I2C protocol.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure containing the LCD configuration.
 * @note This function sets up the LCD display with the appropriate parameters such as 4-bit mode, number of lines, and other settings.
 */
void I2C_LCD_Init(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Clears the LCD display screen.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @note This function resets the cursor to the beginning of the screen and clears the display.
 */
void I2C_LCD_Clear(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Sets the cursor to the home position on the LCD screen.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @note This function moves the cursor to position (0,0) on the screen.
 */
void I2C_LCD_Home(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Sets the cursor to a specific position on the LCD screen.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @param Col Column number where the cursor should be placed.
 * @param Row Row number where the cursor should be placed.
 * @note This function moves the cursor to the specified position (column, row).
 */
void I2C_LCD_SetCursor(I2C_LCD_HandleTypeDef* hi2c, uint8_t Col, uint8_t Row);

/**
 * @brief Displays a single character on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @param Ch The character to be displayed on the screen.
 */
void I2C_LCD_WriteChar(I2C_LCD_HandleTypeDef* hi2c, char Ch);

/**
 * @brief Displays a string of characters on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @param Str Pointer to the string to be displayed on the screen.
 */
void I2C_LCD_WriteString(I2C_LCD_HandleTypeDef* hi2c, char* Str);

/**
 * @brief Shifts the display content to the left.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @note This function shifts all displayed content on the screen to the left.
 */
void I2C_LCD_ShiftLeft(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Shifts the display content to the right.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @note This function shifts all displayed content on the screen to the right.
 */
void I2C_LCD_ShiftRight(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns on the LCD backlight.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_Backlight(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns off the LCD backlight.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_NoBacklight(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns on the display on the LCD.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_Display(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns off the display on the LCD.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_NoDisplay(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns on the cursor on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_Cursor(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns off the cursor on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_NoCursor(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns on the blinking cursor on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_Blink(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Turns off the blinking cursor on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 */
void I2C_LCD_NoBlink(I2C_LCD_HandleTypeDef* hi2c);

/**
 * @brief Creates a custom character on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @param CharIndex The index for the new character (0-7).
 * @param CharMap Pointer to an array containing the definition of the new character (8 bytes).
 */
void I2C_LCD_CreateCustomChar(I2C_LCD_HandleTypeDef* hi2c, uint8_t CharIndex, const uint8_t* CharMap);

/**
 * @brief Displays a custom character on the LCD display.
 * @param hi2c Pointer to the I2C_LCD_HandleTypeDef structure.
 * @param CharIndex The index of the custom character to display (0-7).
 */
void I2C_LCD_PrintCustomChar(I2C_LCD_HandleTypeDef* hi2c, uint8_t CharIndex);


#endif /* INC_I2C_LCD_H_ */
