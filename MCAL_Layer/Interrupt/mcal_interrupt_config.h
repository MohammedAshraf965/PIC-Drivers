/* 
 * File:   mcal_interrupt_config.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:26
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/* Section: Includes */

//#include "../../../packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8/pic/include/proc/pic18f4620.h"
#include "xc.h"
#include "../mcal_std_types.h"
#include "mcal_interrupt_gen_config.h"
#include "mcal_interrupt_manager.h"
#include "../GPIO/hal_gpio.h"

/* Section: Macro Declarations */

#define INTERRUPT_ENABLE                        0x01U
#define INTERRUPT_DISABLE                       0x00U

#define INTERRUPT_TRIGERRED                     0x01U
#define INTERRUPT_NOT_TRIGERRED                 0x00U

#define INTERRUPT_PRIORITY_ENABLE               0x01U
#define INTERRUPT_PRIORITY_DISABLE              0x00U

/* Section: Macro Function Declarations */

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable all priority interrupts   */
#define INTERRUPT_InterruptPriorityEnable()     (RCONbits.IPEN = 1)
/* Disable all priority interrupts  */
#define INTERRUPT_InterruptPriorityDisable()    (RCONbits.IPEN = 0)

/* Enable all high priority interrupts  */
#define INTERRUPT_GlobalInterruptHighEnable()   (INTCONbits.GIEH = 1)
/* Disbale all high priority interrupts */
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH = 0)

/* Enable all low priority interrupts  */
#define INTERRUPT_GlobalInterruptLowEnable()    (INTCONbits.GIEL = 1)
/* Disable all low priority interrupts */
#define INTERRUPT_GlobalInterruptLowDisable()   (INTCONbits.GIEL = 0)

#else

/* Enable all global interrupts  */
#define INTERRUPT_GlobalInterruptEnable()    (INTCONbits.GIE = 1)
/* Disable all global interrupts */
#define INTERRUPT_GlobalInterruptDisable()   (INTCONbits.GIE = 0)

/* Enable all peripheral interrupts  */
#define INTERRUPT_PeripheralInterruptEnable()   (INTCONbits.PEIE = 1)
/* Disable all peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE = 0)

#endif

/* Section: Data Type Declarations */

typedef enum
{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY        
}interrupt_priority_config;

/* Section: Function Declarations */

#endif	/* MCAL_INTERRUPT_CONFIG_H */

