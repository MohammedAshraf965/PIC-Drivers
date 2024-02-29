/* 
 * File:   ecu_7_segment.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/30, 11:31
 */

#ifndef ECU_7_SEGMENT_H
#define	ECU_7_SEGMENT_H

/* Section: Includes */

#include "ecu_7_segment_config.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

#define SEVEN_SEGMENT_CONFIGURATIONS    CONFIG_ENABLE

#define SEVEN_SEGMENT_MAX_NUMBER        9

#define SEGMENT_PIN0                    0
#define SEGMENT_PIN1                    1
#define SEGMENT_PIN2                    2
#define SEGMENT_PIN3                    3


/* Section: Data Type Declarations */

typedef enum
{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct
{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}seven_segment_t;

/* Section: Function Declarations */

Std_ReturnType seven_segment_initialize(const seven_segment_t *_segment);
Std_ReturnType seven_segment_write_number(const seven_segment_t *_segment, uint8 number);

#endif	/* ECU_7_SEGMENT_H */

