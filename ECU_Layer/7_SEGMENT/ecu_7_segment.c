/* 
 * File:   ecu_7_segment.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/30, 11:31
 */

/* Section: Includes */

#include "ecu_7_segment.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Definitions */

/**
 * 
 * @param _segment
 * @return 
 */
#if SEVEN_SEGMENT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType seven_segment_initialize(const seven_segment_t *_segment)
{
    Std_ReturnType ret = E_OK;
    
    if(_segment == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_initialize(&(_segment -> segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialize(&(_segment -> segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialize(&(_segment -> segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialize(&(_segment -> segment_pins[SEGMENT_PIN3]));
    }
    
    return ret;
}
#endif
/**
 * 
 * @param _segment
 * @param number
 * @return 
 */
#if SEVEN_SEGMENT_CONFIGURATIONS == CONFIG_ENABLE
Std_ReturnType seven_segment_write_number(const seven_segment_t *_segment, uint8 number)
{
    Std_ReturnType ret = E_OK;
    
    if((_segment == NULL) || (number > SEVEN_SEGMENT_MAX_NUMBER))
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(_segment -> segment_pins[SEGMENT_PIN0]), number & 0X01);
        ret = gpio_pin_write_logic(&(_segment -> segment_pins[SEGMENT_PIN0]), (number >> 1) & 0X01);
        ret = gpio_pin_write_logic(&(_segment -> segment_pins[SEGMENT_PIN0]), (number >> 2) & 0X01);
        ret = gpio_pin_write_logic(&(_segment -> segment_pins[SEGMENT_PIN0]), (number >> 3) & 0X01);
    }
    
    return ret;    
}
#endif