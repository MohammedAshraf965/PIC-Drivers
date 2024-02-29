/* 
 * File:   hal_gpio.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:06
 */

/* Section: Includes */

#include "hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Function Declarations */

/* Section: Data Type Declarations */

/* Reference to Data Direction Control Registers */
volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to Data Latch Control Registers (Read and Write to Data Latch) */
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to the Port Status Registers */
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/* Section: Function Definitions */

/**
 * @brief Initialize the direction of the pin @ref direction_t
 * @param _pin_config pointer to the configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;

    if((_pin_config == NULL) ||  (_pin_config -> pin > PORT_MAX_PIN_NUMBER - 1))
    {
        ret = E_OK;
    }
    else
    {
        switch (_pin_config -> direction)
        {
            case GPIO_DIRECTION_OUTPUT:
                CLEAR_BIT(*tris_register[_pin_config -> port], _pin_config -> pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SET_BIT(*tris_register[_pin_config -> port], _pin_config -> pin);
                break;
            default:
                ret = E_NOK;
                break;
        }
    
    }
    
    return ret;
}
#endif

/**
 * @brief Return the direction of the pin @ref direction_t 
 * @param _pin_config pointer to the configurations
 * @param direction_status
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status(const pin_config_t * _pin_config, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;

    if ((_pin_config == NULL) || (direction_status == NULL) ||  (_pin_config -> pin > PORT_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_register[_pin_config -> port], _pin_config -> pin);
    }

    return ret;
}
#endif

/**
 * @brief Write the logic of the pin @ref logic_t
 * @param _pin_config pointer to the configurations
 * @param logic
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic)
{
    Std_ReturnType ret = E_OK;

    if(_pin_config == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(logic)
        {
            case GPIO_LOW:
                CLEAR_BIT(*lat_register[_pin_config -> port], _pin_config -> pin);
                break;
            
            case GPIO_HIGH:
                SET_BIT(*lat_register[_pin_config -> port], _pin_config -> pin);
                break;
                
            default:
                ret = E_NOK;
                break;
        }
    }

    return ret;
}
#endif

/**
 * @brief Read the logic of the pin @ref logic_t
 * @param _pin_config pointer to the configurations
 * @param logic
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic)
{
    Std_ReturnType ret = E_OK;

    if((_pin_config == NULL) || (logic == NULL) ||  (_pin_config -> pin > PORT_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOK;
    }
    else
    {
        *logic = READ_BIT(*port_register[_pin_config -> port], _pin_config -> pin);
    }

    return ret;
}
#endif

/**
 * @brief Toggle the logic of the pin @ref logic_t
 * @param _pin_config pointer to the configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;

    if(_pin_config == NULL ||  (_pin_config -> pin > PORT_MAX_PIN_NUMBER - 1))
    {
        ret = E_NOK;
    }
    else
    {
        TOGGLE_BIT(*lat_register[_pin_config -> port], _pin_config -> pin);
    }

    return ret;
}
#endif

/**
 * @brief Initialize the pin @ref pin_index_t
 * @param _pin_config pointer to the configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_PIN_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config)
{
    Std_ReturnType ret = E_OK;
    
    ret = gpio_pin_direction_initialize(_pin_config);
    ret = gpio_pin_write_logic(_pin_config, _pin_config -> logic);
    
    return ret;
}
#endif


/**
 * @brief Initialize the direction of the port @ref port_index_t
 * @param port
 * @param direction
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_PIN_NUMBER - 1)
    {
        ret = E_NOK;
    }
    else
    {
        *tris_register[port] = direction;
    }

    return ret;
}
#endif

/**
 * @brief Return the direction of the port @ref dirdction_t
 * @param port
 * @param direction_status
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_t port, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;
    
    if((port > PORT_MAX_PIN_NUMBER - 1) || (direction_status == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        *direction_status = *tris_register[port];
    }

    return ret;
}
#endif

/**
 * @brief Write the logic of the port @ref logic_t
 * @param port
 * @param logic
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic)
{
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_PIN_NUMBER - 1)
    {
        ret = E_NOK;
    }
    else
    {
        *lat_register[port] = logic;
    }
    return ret;
}
#endif

/**
 * @brief Read the logic of the port @ref logic_t
 * @param port
 * @param logic
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic)
{
    Std_ReturnType ret = E_OK;
    
    if((port > PORT_MAX_PIN_NUMBER - 1) || (logic == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        *logic = *lat_register[port];
    }

    return ret;
}
#endif

/**
 * @brief Toggle the logic of the port @ref port_index_t
 * @param port
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if GPIO_PORT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic(port_index_t port)
{
    Std_ReturnType ret = E_OK;
    
    if(port > PORT_MAX_PIN_NUMBER - 1)
    {
        ret = E_NOK;
    }
    else
    {
        *lat_register[port] ^= PORTC_MASK;
    }
    
    return ret;
}
#endif