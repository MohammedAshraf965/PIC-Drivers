/* 
 * File:   ecu_chr_lcd.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/10, 9:37
 */

/************************** Section: Includes **************************/

#include "ecu_chr_lcd.h"

/************************** Section: Macro Declarations **************************/

/************************** Section: Function Declarations **************************/

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *_lcd, uint8 data_command);
static Std_ReturnType lcd_4bits_send_enable(const chr_lcd_4bit_t *_lcd);
static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *_lcd, uint8 row, uint8 column);

static Std_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *_lcd, uint8 data_command);
static Std_ReturnType lcd_8bits_send_enable(const chr_lcd_8bit_t *_lcd);
static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *_lcd, uint8 row, uint8 column);

/************************** Section: Data Type Definitions   **************************/

/************************** Section: Function Definitions **************************/

/**
 * 
 * @param _lcd
 * @return 
 */
Std_ReturnType lcd_4bit_initialize(const chr_lcd_4bit_t *_lcd)
{
    Std_ReturnType ret = E_NOK;
    uint8 counter = 0;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_initialize(&(_lcd -> lcd_rs));
        ret = gpio_pin_initialize(&(_lcd -> lcd_en));
        
        for(counter = 0; counter < 4; counter ++)
        {
            ret = gpio_pin_initialize(&(_lcd -> lcd_data[counter]));
        }
        
            __delay_ms(20);
            ret |= lcd_4bit_send_command(_lcd, LCD_4BIT_MODE_2_LINE);
            __delay_ms(5);
            ret |= lcd_4bit_send_command(_lcd, LCD_4BIT_MODE_2_LINE);
            __delay_us(150);
            ret |= lcd_4bit_send_command(_lcd, LCD_4BIT_MODE_2_LINE);
            ret |= lcd_4bit_send_command(_lcd, LCD_CLEAR);
            ret |= lcd_4bit_send_command(_lcd, LCD_RETURN_HOME);
            ret |= lcd_4bit_send_command(_lcd, LCD_ENTRY_MODE);
            ret |= lcd_4bit_send_command(_lcd, LCD_CURSOR_OFF_DISPLAY_ON);
            ret |= lcd_4bit_send_command(_lcd, LCD_4BIT_MODE_2_LINE);
            ret |= lcd_4bit_send_command(_lcd, LCD_DDRAM_START);
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *_lcd, uint8 command)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd -> lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(_lcd, command >> 4);
        ret = lcd_4bits_send_enable(_lcd);
        ret = lcd_send_4bits(_lcd, command);
        ret = lcd_4bits_send_enable(_lcd);
    }
    
    return ret ; 
}

/**
 * 
 * @param _lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *_lcd, uint8 data)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd -> lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(_lcd, data >> 4);
        ret = lcd_4bits_send_enable(_lcd);
        ret = lcd_send_4bits(_lcd, data);
        ret = lcd_4bits_send_enable(_lcd);
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *_lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = lcd_4bits_set_cursor(_lcd, row, column);
        ret = lcd_4bit_send_char_data(_lcd, data);
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *_lcd, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if((_lcd == NULL) || (str == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(_lcd, *str++);
        }
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *_lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if((_lcd == NULL) || (str == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        ret = lcd_4bits_set_cursor(_lcd, row, column);
        while(*str)
        {
            ret = lcd_4bit_send_char_data(_lcd, *str++);
        }
    }
    
    return ret ; 
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *_lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        
    }
    
    return ret ;
}


/**
 * 
 * @param _lcd
 * @return 
 */
Std_ReturnType lcd_8bit_initialize(const chr_lcd_8bit_t *_lcd)
{
    Std_ReturnType ret = E_NOK;
    uint8 counter = 0;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_initialize(&(_lcd -> lcd_rs));
        ret = gpio_pin_initialize(&(_lcd -> lcd_en));
        
        for(counter = 0; counter < 8; counter ++)
        {
            ret = gpio_pin_initialize(&(_lcd -> lcd_data[counter]));
        }
        
            __delay_ms(20);
            ret |= lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
            __delay_ms(5);
            ret |= lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
            __delay_us(150);
            ret |= lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
            ret |= lcd_8bit_send_command(_lcd, LCD_CLEAR);
            ret |= lcd_8bit_send_command(_lcd, LCD_RETURN_HOME);
            ret |= lcd_8bit_send_command(_lcd, LCD_ENTRY_MODE);
            ret |= lcd_8bit_send_command(_lcd, LCD_CURSOR_OFF_DISPLAY_ON);
            ret |= lcd_8bit_send_command(_lcd, LCD_8BIT_MODE_2_LINE);
            ret |= lcd_8bit_send_command(_lcd, LCD_DDRAM_START);
    }
    
    return ret ;  
}

/**
 * 
 * @param _lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *_lcd, uint8 command)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd -> lcd_rs), GPIO_LOW);
        ret |= lcd_send_8bits(_lcd, command);
        ret |= lcd_8bits_send_enable(_lcd);
    }
    
    return ret ; 
}

/**
 * 
 * @param _lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *_lcd, uint8 data)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd -> lcd_rs), GPIO_HIGH);
        ret |= lcd_send_8bits(_lcd, data);
        ret |= lcd_8bits_send_enable(_lcd);
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *_lcd, uint8 row, uint8 column, uint8 data)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = lcd_8bits_set_cursor(_lcd, row, column);
        ret = lcd_8bit_send_char_data(_lcd, data);
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *_lcd, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if((_lcd == NULL) || (str == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(_lcd, *str++);
        }
    }
    
    return ret ;
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *_lcd, uint8 row, uint8 column, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if((_lcd == NULL) || (str == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        ret = lcd_8bits_set_cursor(_lcd, row, column);
        
        while(*str)
        {
            ret = lcd_8bit_send_char_data(_lcd, *str++);
        }
    }
    
    return ret ; 
}

/**
 * 
 * @param _lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *_lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos)
{
    Std_ReturnType ret = E_NOK;
    uint8 counter = 0;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = lcd_8bit_send_command(_lcd, (LCD_CGRAM_START + (mem_pos*8)));
        
        for(counter = 0; counter < 8; counter++)
        {
            ret = lcd_8bit_send_char_data(_lcd, chr[counter]);
        }
        
        ret = lcd_8bit_send_char_data_pos(_lcd, row, column, mem_pos);
    }
    
    return ret ;
}


Std_ReturnType convert_byte_to_string(uint8 value, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if(str == NULL)
    {
        ret = E_NOK;
    }
    else
    {
       memset(str, '\0', 4);
       sprintf(str "%i", value);
       ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType convert_short_to_string(uint16 value, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if(str == NULL)
    {
        ret = E_NOK;
    }
    else
    {
       memset(str, '\0', 6);
       sprintf(str "%i", value);
       ret = E_OK;
    }
    
    return ret ;
}

Std_ReturnType convert_int_to_string(uint32 value, uint8 *str)
{
    Std_ReturnType ret = E_NOK;
    
    if(str == NULL)
    {
        ret = E_NOK;
    }
    else
    {
       memset(str, '\0', 11);
       sprintf(str "%i", value);
       ret = E_OK;
    }
    
    return ret ;
}

static Std_ReturnType lcd_send_4bits(const chr_lcd_4bit_t *_lcd, uint8 data_command)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_lcd -> lcd_data[0]), (data_command >> 0) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd -> lcd_data[1]), (data_command >> 1) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd -> lcd_data[2]), (data_command >> 2) & (uint8)0x01);
        ret = gpio_pin_write_logic(&(_lcd -> lcd_data[3]), (data_command >> 3) & (uint8)0x01);
    }
    
    return ret ;  
}

static Std_ReturnType lcd_4bits_send_enable(const chr_lcd_4bit_t *_lcd)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret |= gpio_pin_write_logic(&(_lcd -> lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret |= gpio_pin_write_logic(&(_lcd -> lcd_en), GPIO_LOW);
    }
    
    return ret ;  
}

static Std_ReturnType lcd_4bits_set_cursor(const chr_lcd_4bit_t *_lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_NOK;
    column--;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(row)
        {
            case ROW_1:
                ret = lcd_4bit_send_command(_lcd, (0x80 + column)); 
                break;
            case ROW_2:
                ret = lcd_4bit_send_command(_lcd, (0xc0 + column)); 
                break;
            case ROW_3:
                ret = lcd_4bit_send_command(_lcd, (0X94 + column)); 
                break;
            case ROW_4:
                ret = lcd_4bit_send_command(_lcd, (0xd4 + column)); 
                break;
            default: ;
        }
    }
    
    return ret ;  
}

static Std_ReturnType lcd_send_8bits(const chr_lcd_8bit_t *_lcd, uint8 data_command)
{
    Std_ReturnType ret = E_NOK;
    uint8 counter = 0;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        for(counter = 0; counter < 8; counter++)
        {
            ret = gpio_pin_write_logic(&(_lcd -> lcd_data[counter]), (data_command >> counter) & (uint8)0x01);
        }
    }
    
    return ret ;  
}

static Std_ReturnType lcd_8bits_send_enable(const chr_lcd_8bit_t *_lcd)
{
    Std_ReturnType ret = E_NOK;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret |= gpio_pin_write_logic(&(_lcd -> lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret |= gpio_pin_write_logic(&(_lcd -> lcd_en), GPIO_LOW);
    }
    
    return ret ;  
}

static Std_ReturnType lcd_8bits_set_cursor(const chr_lcd_8bit_t *_lcd, uint8 row, uint8 column)
{
    Std_ReturnType ret = E_NOK;
    column--;
    
    if(_lcd == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(row)
        {
            case ROW_1:
                ret = lcd_8bit_send_command(_lcd, (0x80 + column)); 
                break;
            case ROW_2:
                ret = lcd_8bit_send_command(_lcd, (0xc0 + column)); 
                break;
            case ROW_3:
                ret = lcd_8bit_send_command(_lcd, (0X94 + column)); 
                break;
            case ROW_4:
                ret = lcd_8bit_send_command(_lcd, (0xd4 + column)); 
                break;
            default: ;
        }
    }
    
    return ret ;  
}