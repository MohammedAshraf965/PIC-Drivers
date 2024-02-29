/* 
 * File:   hal_timer0.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/11, 12:40
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/************************** Section: Includes **************************/

#include "xc.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/************************** Section: Macro Declarations **************************/

#define TIMER0_PRESCALER_ENABLE_CFG                     1
#define TIMER0_PRESCALER_DISABLE_CFG                    0

#define TIMER0_RISING_EDGE_CFG                          1
#define TIMER0_FALLING_EDGE_CFG                         0

#define TIMER0_TIMER_MODE_CFG                           1
#define TIMER0_COUNTER_MODE_CFG                         0

#define TIMER0_8BIT_MODE                                1
#define TIMER0_16BIT_MODE                               0

/************************** Section: Macro Function Declarations **************************/

#define TIMER0_CONFIG_DISABLE                        (T0CONbits.TMR0ON = 0)
#define TIMER0_CONFIG_ENABLE                         (T0CONbits.TMR0ON = 1)

#define TIMER0_CLOCK_TIMER_MODE                     (T0CONbits.T0CS = 0)
#define TIMER0_CLOCK_COUNTER_MODE                   (T0CONbits.T0CS = 1)

#define TIMER0_INCREMENT_ON_RISINNG_EDGE            (T0CONbits.T0SE = 0)
#define TIMER0_INCREMENT_ON_FALLING_EDGE            (T0CONbits.T0SE = 1)

#define TIMER0_16BIT_CONFIG                         (T0CONbits.T08BIT = 0)
#define TIMER0_8BIT_CONFIG                          (T0CONbits.T08BIT = 1)

#define TIMER0_PRESCALER_DISABLE                    (T0CONbits.PSA = 1)
#define TIMER0_PRESCALER_ENABLE                     (T0CONbits.PSA = 0)

/************************** Section: Data Type Declarations **************************/

typedef enum
{
    TIMER0_PRESCALER_DIV_BY_2,
    TIMER0_PRESCALER_DIV_BY_4,
    TIMER0_PRESCALER_DIV_BY_6,
    TIMER0_PRESCALER_DIV_BY_8,
    TIMER0_PRESCALER_DIV_BY_32,
    TIMER0_PRESCALER_DIV_BY_64,
    TIMER0_PRESCALER_DIV_BY_128,
    TIMER0_PRESCALER_DIV_BY_256,        
}Timer0_prescaler_select_t;

typedef struct
{
    #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        void (* TIMER0_InterruptHandler)(void);
        interrupt_priority_config priority;
    #endif
    Timer0_prescaler_select_t prescaler_val;
    uint16 preload_value;
    uint8 prescaler_status      :1;
    uint8 timer0_counter_edge   :1;
    uint8 timer0_clock_mode     :1;
    uint8 timer0_register_size  :1;
    uint8 timer0_reserved       :4;
}Timer0_t;

typedef void (* TMR0_InterruptHandler)(void);


/************************** Section: Function Declarations **************************/

Std_ReturnType Timer0_Init(const Timer0_t *_timer);
Std_ReturnType Timer0_DeInit(const Timer0_t *_timer);
Std_ReturnType Timer0_Read_Value(const Timer0_t *_timer, uint16 *value);
Std_ReturnType Timer0_Write_Value(const Timer0_t *_timer, uint16 value);

#endif	/* HAL_TIMER0_H */

