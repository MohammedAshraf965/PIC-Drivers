/* 
 * File:   ecu_dc_motor.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/29, 11:32
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/* Section: Includes */

#include "ecu_dc_motor_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define DC_MOTOR_STATUS_ON      0x01U
#define DC_MOTOR_STATUS_OFF     0x00U

#define DC_MOTOR_CONFIGURATIONS CONFIG_ENABLE

#define DC_MOTOR_PIN1           0x00U
#define DC_MOTOR_PIN2           0x01U

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

typedef struct
{
    pin_config_t dc_motor_pin[2];
}dc_motor_t;

/* Section: Function Declarations */

Std_ReturnType dc_motor_initialize(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);

#endif	/* ECU_DC_MOTOR_H */

