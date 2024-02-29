/* 
 * File:   ecu_led.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:15
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/* Section: Includes */

#include "ecu_led_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define LED_CONFIGURATIONS CONFIG_ENABLE

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

typedef enum
{
    LED_OFF,
    LED_ON
}led_status;

typedef struct
{
    uint8 portname:     4;
    uint8 pin:          3;
    uint8 led_status:   1;
}led_t;

/* Section: Function Declarations */

Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_switch_on(const led_t *led);
Std_ReturnType led_switch_off(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);

#endif	/* ECU_LED_H */

