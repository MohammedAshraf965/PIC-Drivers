/* 
 * File:   mcal_external_interrupt.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:27
 */

#ifndef MCAL_EXTERNAL_INTERRUPT_H
#define	MCAL_EXTERNAL_INTERRUPT_H

/* Section: Includes */

#include "mcal_interrupt_config.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

#if EXTERNAL_INTERRUPT_INTx_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable external interrupts INT0  */
#define EXT_INT0_InterruptEnable()                  (INTCONbits.INT0E = 1)
/* Disable external interrupts INT0 */
#define EXT_INT0_InterruptDisable()                 (INTCONbits.INT0E = 0)
/* Clears external interrupts INT0 */
#define EXT_INT0_InterruptFlagClear()               (INTCONbits.INT0F = 0)
/* Triggers external interrupts INT0 at the rising edge */
#define EXT0_INT0_Rising_Edge()                     (INTCON2bits.INTEDG0 = 1)
/* Triggers external interrupts INT0 at the falling edge */
#define EXT0_INT0_Falling_Edge()                    (INTCON2bits.INTEDG0 = 0)

/* Enable external interrupts INT1  */
#define EXT_INT1_InterruptEnable()                  (INTCON3bits.INT1E = 1)
/* Disable external interrupts INT1 */
#define EXT_INT1_InterruptDisable()                 (INTCON3bits.INT1E = 0)
/* Clears external interrupts INT1 */
#define EXT_INT1_InterruptFlagClear()               (INTCON3bits.INT1F = 0)
/* Triggers external interrupts INT1 at the rising edge */
#define EXT_INT1_Rising_Edge()                      (INTCON2bits.INTEDG1 = 1)
/* Triggers external interrupts INT1 at the falling edge */
#define EXT_INT1_Falling_Edge()                     (INTCON2bits.INTEDG1 = 0)

/* Enable external interrupts INT2  */
#define EXT_INT2_InterruptEnable()                  (INTCON3bits.INT2E = 1)
/* Disable external interrupts INT2 */
#define EXT_INT2_InterruptDisable()                 (INTCON3bits.INT2E = 0)
/* Clears external interrupts INT2 */
#define EXT_INT2_InterruptFlagClear()               (INTCON3bits.INT2F = 0)
/* Triggers external interrupts INT2 at the rising edge */
#define EXT_INT2_Rising_Edge()                      (INTCON2bits.INTEDG2 = 1)
/* Triggers external interrupts INT2 at the falling edge */
#define EXT_INT2_Falling_Edge()                     (INTCON2bits.INTEDG2 = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable external interrupts INT1 priority  */
#define EXT_INT1_HighPrioritySet()                  (INTCON3bits.INT1P = 1)
/* Disable external interrupts INT1 priority */
#define EXT_INT1_LowPrioritySet()                   (INTCON3bits.INT1P = 0)

/* Enable external interrupts INT2 priority  */
#define EXT_INT2_HighPrioritySet()                  (INTCON3bits.INT2P = 1)
/* Disable external interrupts INT2 priority */
#define EXT_INT2_LowPrioritySet()                   (INTCON3bits.INT2P = 0)

#endif

#endif

#if EXTERNAL_INTERRUPT_OnChange_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable the external interrupts RBx  */
#define EXT_RBx_InterruptEnable()                    (INTCONbits.RBIE = 1)
/* Disable the external interrupts RBx */
#define EXT_RBx_InterruptDisable()                   (INTCONbits.RBIE = 0)
/* Clears the flag of the external interrupts RBx */
#define EXT_RBx_InterruptFlagClear()                 (INTCONbits.RBIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable the external interrupts RBx priority to be high priority */
#define EXT_RBx_InterruptHighPriority()           (INTCON2bits.RBIP = 1)
/* Enable the external interrupts RBx priority to be low priority */
#define EXT_RBx_InterruptLowPriority()           (INTCON2bits.RBIP = 0)

#endif

#endif

/* Section: Data Type Declarations */

typedef void (* InterruptHandler)(void);

typedef enum
{
    INTERRUPT_FALLING_EDGE = 0,
    INTERRUPT_RISING_EDGE
}interrupt_INTx_edge;

typedef enum
{
    INTERRUPT_EXTERNAL_INT0 = 0,
    INTERRUPT_EXTERNAL_INT1,
    INTERRUPT_EXTERNAL_INT2        
}interrupt_INTx_src;

typedef struct
{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_INTx_edge edge;
    interrupt_INTx_src source;
    interrupt_priority_config priority;
}interrupt_INTx_t;

typedef struct
{
    void (* EXT_InterruptHandler)(void);
    pin_config_t mcu_pin;
    interrupt_priority_config priority;
}interrupt_RBx_t;

/* Section: Function Declarations */

Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj);
Std_ReturnType interrupt_RBx_Init(const interrupt_RBx_t *rb_obj);
Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t *rb_obj);

#endif	/* MCAL_EXTERNAL_INTERRUPT_H */