/* 
 * File:   ecu_keypad.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/08, 10:05
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/************************** Section: Includes **************************/

#include "ecu_keypad_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/************************** Section: Macro Declarations **************************/

#define ECU_KEYPAD_ROWS                     0x04
#define ECU_KEYPAD_COLUMNS                  0x04

/************************** Section: Macro Function Declarations **************************/

/************************** Section: Data Type Declarations **************************/

typedef struct
{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_column_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/************************** Section: Function Declarations **************************/

Std_ReturnType Keypad_Initialize(keypad_t *keypad_obj);
Std_ReturnType Keypad_get_value(keypad_t *keypad_obj, uint8 *val);

#endif	/* ECU_KEYPAD_H */

