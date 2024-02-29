/* 
 * File:   ecu_led.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:15
 */

/* Section: Includes */

#include "ecu_led.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Definitions */

/**
 * @brief Initializes the LED @ref led_t
 * @param led pointer to the led module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if LED_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType led_initialize(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(led == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led -> portname, .pin = led -> pin, 
                .direction = GPIO_DIRECTION_OUTPUT, .logic = led -> led_status};
    
        gpio_pin_initialize(&pin_obj);
    }
    
    return ret;
}
#endif

/**
 * @brief Swtiches ON the LED @ref led_status 
 * @param led pointer to the led module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if LED_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType led_switch_on(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(led == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led -> portname, .pin = led -> pin, 
                .direction = GPIO_DIRECTION_OUTPUT, .logic = led -> led_status};
        
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    
    return ret;
}
#endif

/**
 * @brief Swtiches OFF the LED @ref led_status 
 * @param led pointer to the led module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if LED_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType led_switch_off(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(led == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led -> portname, .pin = led -> pin, 
                .direction = GPIO_DIRECTION_OUTPUT, .logic = led -> led_status};
        
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    
    return ret;
}
#endif

/**
 * @brief Toggles the LED @ref led_status 
 * @param led pointer to the led module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if LED_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType led_toggle(const led_t *led)
{
    Std_ReturnType ret = E_OK;
    
    if(led == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = {.port = led -> portname, .pin = led -> pin, 
                .direction = GPIO_DIRECTION_OUTPUT, .logic = led -> led_status};
        
        gpio_pin_toggle_logic(&pin_obj);
    }
    
    return ret;
}
#endif