/* 
 * File:   ecu_dc_motor.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/29, 11:32
 */

/* Section: Includes */

#include "ecu_dc_motor.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Definitions */

/**
 * @brief Initialize the dc motor @ref dc_motor_t
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if DC_MOTOR_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(_dc_motor == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        gpio_pin_direction_initialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_direction_initialize(&(_dc_motor->dc_motor_pin[1]));  
    }
    
    return ret;
}
#endif

/**
 * @brief Move the dc motor to the right @ref dc_motor_pin_t
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if DC_MOTOR_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(_dc_motor == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);   
    }
    
    return ret;   
}
#endif

/**
 * @brief Move the dc motor to the left @ref dc_motor_pin_t
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if DC_MOTOR_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(_dc_motor == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_HIGH);   
    }
    
    return ret;     
}
#endif

/**
 * @brief Stop the dc motor @ref dc_motor_pin_t
 * @param dc_motor pointer to the dc motor module configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
#if DC_MOTOR_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    Std_ReturnType ret = E_OK;
    
    if(_dc_motor == NULL)
    {
        ret = E_NOK;
    }
    else
    {   
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
    }
    
    return ret;  
}
#endif