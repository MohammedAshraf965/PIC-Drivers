/* 
 * File:   ecu_keypad.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/08, 10:05
 */

/* Section: Includes */

#include "ecu_keypad.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

static const uint8 btn_val[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = 
{
    {'7', '8', '9', '/'},
    {'4', '5', '6', '*'},
    {'1', '2', '3', '-'},
    {'#', '0', '=', '+'},        
            
};

/* Section: Function Declarations */

/**
 * 
 * @param keypad_obj
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType Keypad_Initialize(keypad_t *keypad_obj)
{
    Std_ReturnType ret = E_NOK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT;
    
    if(keypad_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        for(rows_counter = ZERO_INIT; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            ret = gpio_pin_initialize(&(keypad_obj -> keypad_row_pins[rows_counter]));
        }
        
        for(columns_counter = ZERO_INIT; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
        {
            ret = gpio_pin_direction_initialize(&(keypad_obj -> keypad_column_pins[columns_counter]));
        }
    }
    
    return ret;
}

/**
 * 
 * @param keypad_obj
 * @param val
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType Keypad_get_value(keypad_t *keypad_obj, uint8 *val)
{
    Std_ReturnType ret = E_NOK;
    uint8 rows_counter = ZERO_INIT, columns_counter = ZERO_INIT, l_counter = ZERO_INIT;
    uint8 column_logic = ZERO_INIT;
    
    if(keypad_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        for(rows_counter = ZERO_INIT; rows_counter < ECU_KEYPAD_ROWS; rows_counter++)
        {
            for(l_counter = ZERO_INIT; l_counter < ECU_KEYPAD_ROWS; l_counter++)
            {
                ret = gpio_pin_write_logic(&(keypad_obj -> keypad_row_pins[l_counter]), GPIO_LOW);
            }
            
            ret = gpio_pin_write_logic(&(keypad_obj -> keypad_row_pins[rows_counter]), GPIO_HIGH);
            
            __delay_ms(10);
            
            for(columns_counter = ZERO_INIT; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++)
            {
                ret = gpio_pin_read_logic(&(keypad_obj -> keypad_column_pins[columns_counter]), &column_logic);
                
                if(column_logic == GPIO_HIGH)
                {
                    *val = btn_val[rows_counter][columns_counter];
                }
            }
        }
    }
    
    return ret;
}
