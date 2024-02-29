/* 
 * File:   mcal_internal_interrupt.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:27
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* Section: Includes */

#include "mcal_interrupt_config.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Clear the interrupt enable for the ADC module */
#define ADC_InterruptDisable()                  (PIE1bits.ADIE = 0)

/* Set the interrupt enable for the ADC module */
#define ADC_InterruptEnable()                   (PIE1bits.ADIE = 1)

/* Clear the interrupt flag of the ADC module */
#define ADC_InterruptFlagClear()                (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable ADC interrupts HIGH priority  */
#define ADC_HighPrioritySet()                  (IPR1bits.ADIP = 1)
/* Disable ADC interrupts LOW priority */
#define ADC_LowPrioritySet()                   (IPR1bits.ADIP = 0)

#endif

#endif

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Clear the interrupt enable for the Timer0 module */
#define TIMER0_InterruptDisable()                  (INTCONbits.TMR0IE = 0)

/* Set the interrupt enable for the Timer0 module */
#define TIMER0_InterruptEnable()                   (INTCONbits.TMR0IE = 1)

/* Clear the interrupt flag of the Timer0 module */
#define TIMER0_InterruptFlagClear()                (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* Enable Timer0 interrupts HIGH priority  */
#define TIMER0_HighPrioritySet()                  (INTCON2bits.TMR0IP = 1)
/* Disable Timer0 interrupts LOW priority */
#define TIMER0_LowPrioritySet()                   (INTCON2bits.TMR0IP = 0)

#endif

#endif


/* Section: Data Type Declarations */

typedef void (* ADCInterruptHandler)(void);

/* Section: Function Declarations */

#endif	/* MCAL_INTERNAL_INTERRUPT_H */

