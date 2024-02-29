/* 
 * File:   ecu_relay.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/29, 9:56
 */

/* Section: Includes */

#include "ecu_relay.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */


/* Section: Data Type Declarations */


/* Section: Function Definitions */

/**
 * @brief Initializes the relay @ref relay_t
 * @param relay pointer to the relay module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if RELAY_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType relay_initialize(const relay_t *relay)
{
    Std_ReturnType ret = E_NOK;
    
    if(relay == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = { .port = relay -> relay_port, 
                                 .pin = relay -> relay_pin,
                                 .direction = GPIO_DIRECTION_OUTPUT,
                                 .logic = GPIO_LOW
        };
        
        gpio_pin_direction_initialize(&pin_obj);
    }
    
    return ret;
}
#endif

/**
 * @brief Initializes the relay @ref relay_t
 * @param relay pointer to the relay module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if RELAY_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType relay_turn_on(const relay_t *relay)
{
    Std_ReturnType ret = E_NOK;
    
    if(relay == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = { .port = relay -> relay_port, 
                                 .pin = relay -> relay_pin,
                                 .direction = GPIO_DIRECTION_OUTPUT,
                                 .logic = GPIO_LOW
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    
    return ret;  
}
#endif

/**
 * @brief Initializes the relay @ref relay_t
 * @param relay pointer to the relay module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if RELAY_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType relay_turn_off(const relay_t *relay)
{
    Std_ReturnType ret = E_NOK;
    
    if(relay == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        pin_config_t pin_obj = { .port = relay -> relay_port, 
                                 .pin = relay -> relay_pin,
                                 .direction = GPIO_DIRECTION_OUTPUT,
                                 .logic = GPIO_LOW
        };
        
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    
    return ret;
}
#endif