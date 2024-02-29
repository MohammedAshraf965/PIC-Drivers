/* 
 * File:   ecu_button.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/28, 14:15
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/* Section: Includes */

#include "ecu_button_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define BUTTON_CONFIGUTATIONS   CONFIG_ENABLE

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

typedef enum
{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct
{
    pin_config_t    button_pin;
    button_state_t  button_state;
    button_active_t button_connection;
}button_t;

/* Section: Function Declarations */

Std_ReturnType button_initialize(button_t *btn);
Std_ReturnType button_read(button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

