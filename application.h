/* 
 * File:   application.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:18
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section: Includes */

#include "ECU_Layer/ecu_layer_init.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

extern keypad_t keypad_1;
extern chr_lcd_4bit_t lcd_4bit;
extern chr_lcd_8bit_t lcd_8bit;
extern usart_t usart_obj;

/* Section: Function Declarations */

void application_initialize(void);

#endif	/* APPLICATION_H */

