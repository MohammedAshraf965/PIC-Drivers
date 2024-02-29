/* 
 * File:   ecu_button.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/28, 14:15
 */

/* Section: Includes */

#include "ecu_button.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Definitions */

/**
 * @breif Initialize the button pin @ref button_t
 * @param btn pointer to the button module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if BUTTON_CONFIGUTATIONS == CONFIG_ENABLE
Std_ReturnType button_initialize(button_t *btn)
{
    Std_ReturnType ret = E_OK;
    
    if(btn == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(btn -> button_pin));
    }
    
    return ret;
}
#endif

/**
 * @breif Read the button pin @ref button_state_t
 * @param btn pointer to the button module configurations
 * @param btn_state stores the state of the button
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if BUTTON_CONFIGUTATIONS == CONFIG_ENABLE
Std_ReturnType button_read(button_t *btn, button_state_t *btn_state)
{
    Std_ReturnType ret = E_OK;
    logic_t Pin_Logic = GPIO_LOW;
    
    if((btn == NULL) || (btn_state == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        gpio_pin_read_logic(&(btn -> button_pin), &Pin_Logic);
        
        if(btn -> button_connection == BUTTON_ACTIVE_HIGH)
        {
            if(Pin_Logic == GPIO_HIGH)
            {
                *btn_state = BUTTON_PRESSED;
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else if(btn -> button_connection == BUTTON_ACTIVE_LOW)
        {
            if(Pin_Logic == GPIO_HIGH)
            {
                *btn_state = BUTTON_RELEASED;
            }
            else
            {
                *btn_state = BUTTON_PRESSED;
            }
        }
        else
        {
            
        }
    }
    
    return ret;
}
#endif