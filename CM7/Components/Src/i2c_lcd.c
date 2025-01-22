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

/*-------------------------[Private includes]-------------------------*/

#include <utils.h>
#include "i2c_lcd.h"

/*-----------------------[INTERNAL DEFINITIONS]-----------------------*/
// CMD
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80
// DISPLAY ENTRY
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
// DISPLAY CONTROL
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00
// CURSOR MOTION
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00
// FUNCTION SET
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00
// BACKLIGHT CONTROL
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00
#define EN                      0b00000100  // Enable bit
#define RW                      0b00000010  // Read/Write bit
#define RS                      0b00000001  // Register select bit

/*-----------------------[INTERNAL VARIABLES]-----------------------*/


/*---------------------[STATIC INTERNAL FUNCTIONS]-----------------------*/

static void I2C_LCD_ExpanderWrite(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t DATA)
{
    uint8_t TxData = (DATA) | hi2c_lcd->BacklightVal;
    HAL_I2C_Master_Transmit(hi2c_lcd->hi2c, (hi2c_lcd->I2C_LCD_Address<<1), &TxData, sizeof(TxData), 100);
}

static void I2C_LCD_EnPulse(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t DATA)
{
	I2C_LCD_ExpanderWrite(hi2c_lcd, (DATA | EN)); // En high
	DELAY_US(2); // enable pulse must be >450ns

    I2C_LCD_ExpanderWrite(hi2c_lcd, (DATA & ~EN)); // En low
    DELAY_US(50); // commands need > 37us to settle
}

static void I2C_LCD_Write4Bits(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t Val)
{
	I2C_LCD_ExpanderWrite(hi2c_lcd, Val);
	I2C_LCD_EnPulse(hi2c_lcd, Val);
}

static void I2C_LCD_Send(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t Val, uint8_t Mode)
{
    uint8_t HighNib = Val & 0xF0;
    uint8_t LowNib = (Val << 4) & 0xF0;
    I2C_LCD_Write4Bits(hi2c_lcd, (HighNib) | Mode);
    I2C_LCD_Write4Bits(hi2c_lcd, (LowNib) | Mode);
}

static void I2C_LCD_Cmd(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t CMD)
{
	I2C_LCD_Send(hi2c_lcd, CMD, 0);
}

static void I2C_LCD_Data(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t DATA)
{
	I2C_LCD_Send(hi2c_lcd, DATA, 1);
}

/*-----------------------------------------------------------------------*/

//=========================================================================================================================

/*-----------------------[USER EXTERNAL FUNCTIONS]-----------------------*/

void I2C_LCD_Init(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	// According To Datasheet, We Must Wait At Least 40ms After Power Up Before Interacting With The LCD Module
	while(HAL_GetTick() < 50);
    I2C_LCD_Cmd(hi2c_lcd, 0x30);
    DELAY_MS(5);  // Delay > 4.1ms
    I2C_LCD_Cmd(hi2c_lcd, 0x30);
    DELAY_MS(5);  // Delay > 4.1ms
    I2C_LCD_Cmd(hi2c_lcd, 0x30);
    DELAY_US(150);  // Delay > 100μs
    I2C_LCD_Cmd(hi2c_lcd, 0x02);
    // Configure the LCD
    I2C_LCD_Cmd(hi2c_lcd, LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);
    I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
    I2C_LCD_Cmd(hi2c_lcd, LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
    hi2c_lcd->DisplayCtrl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    hi2c_lcd->BacklightVal = LCD_BACKLIGHT;
    // Clear the LCD
    I2C_LCD_Clear(hi2c_lcd);
}

void I2C_LCD_Clear(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
    I2C_LCD_Cmd(hi2c_lcd, LCD_CLEARDISPLAY);
    DELAY_MS(2);
}

void I2C_LCD_Home(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
    I2C_LCD_Cmd(hi2c_lcd, LCD_RETURNHOME);
    DELAY_MS(2);
}

void I2C_LCD_SetCursor(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t Col, uint8_t Row)
{
    int Row_Offsets[] = {0x00, 0x40, 0x14, 0x54};
    if (Row > hi2c_lcd->I2C_LCD_nRow)
    {
    	Row = hi2c_lcd->I2C_LCD_nRow - 1;
    }
    I2C_LCD_Cmd(hi2c_lcd, LCD_SETDDRAMADDR | (Col + Row_Offsets[Row]));
}

void I2C_LCD_WriteChar(I2C_LCD_HandleTypeDef* hi2c_lcd, char Ch)
{
    I2C_LCD_Data(hi2c_lcd, Ch);
}

void I2C_LCD_WriteString(I2C_LCD_HandleTypeDef* hi2c_lcd, char *Str)
{
    while (*Str)
    {
        I2C_LCD_Data(hi2c_lcd, *Str++);
    }
}

void I2C_LCD_ShiftLeft(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
    I2C_LCD_Cmd(hi2c_lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void I2C_LCD_ShiftRight(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
    I2C_LCD_Cmd(hi2c_lcd, LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void I2C_LCD_Backlight(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->BacklightVal = LCD_BACKLIGHT;
    I2C_LCD_ExpanderWrite(hi2c_lcd, 0);
}

void I2C_LCD_NoBacklight(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->BacklightVal = LCD_NOBACKLIGHT;
    I2C_LCD_ExpanderWrite(hi2c_lcd, 0);
}

void I2C_LCD_Display(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl |= LCD_DISPLAYON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_NoDisplay(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl &= ~LCD_DISPLAYON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_Cursor(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl |= LCD_CURSORON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_NoCursor(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl &= ~LCD_CURSORON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_Blink(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl |= LCD_BLINKON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_NoBlink(I2C_LCD_HandleTypeDef* hi2c_lcd)
{
	hi2c_lcd->DisplayCtrl &= ~LCD_BLINKON;
	I2C_LCD_Cmd(hi2c_lcd, LCD_DISPLAYCONTROL | hi2c_lcd->DisplayCtrl);
}

void I2C_LCD_CreateCustomChar(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t CharIndex, const uint8_t* CharMap)
{
    CharIndex &= 0x07;
    I2C_LCD_Cmd(hi2c_lcd, LCD_SETCGRAMADDR | (CharIndex << 3));
    for (int i = 0; i < 8; i++)
    {
    	I2C_LCD_Send(hi2c_lcd, CharMap[i], RS);
    }
}

void I2C_LCD_PrintCustomChar(I2C_LCD_HandleTypeDef* hi2c_lcd, uint8_t CharIndex)
{
	I2C_LCD_Send(hi2c_lcd, CharIndex, RS);
}
