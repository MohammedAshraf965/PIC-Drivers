/* 
 * File:   ecu_layer_init.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/08, 10:31
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section: Includes */

#include "BUTTON/ecu_button.h"
#include "LED/ecu_led.h"
#include "RELAY/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "7_SEGMENT/ecu_7_segment.h"
#include "KEYPAD/ecu_keypad.h"
#include "CHR_LCD/ecu_chr_lcd.h"

#include "../MCAL_Layer/ADC/hal_adc.h"
#include "../MCAL_Layer/USART/hal_usart.h"
#include "../MCAL_Layer/EEPROM/hal_eeprom.h"
#include "../MCAL_Layer/Timer/hal_timer0.h"
#include "../MCAL_Layer/Interrupt/mcal_external_interrupt.h"

/* Section: Macro Declarations */

#define _XTAL_FREQ      8000000UL

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

void ecu_layer_init(void);

#endif	/* ECU_LAYER_INIT_H */

