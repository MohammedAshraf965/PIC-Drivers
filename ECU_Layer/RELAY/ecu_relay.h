/* 
 * File:   ecu_relay.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/29, 9:56
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section: Includes */

#include "ecu_relay_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define RELAY_ON_STATUS     0x01U
#define RELAY_OFF_STATUS    0x00U

#define RELAY_CONFIGURATIONS CONFIG_ENABLE

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

typedef struct
{
    uint8 relay_port    :4;
    uint8 relay_pin     :3;
    uint8 relay_status  :1;
}relay_t;

/* Section: Function Declarations */

Std_ReturnType relay_initialize(const relay_t *relay);
Std_ReturnType relay_turn_on(const relay_t *relay);
Std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

