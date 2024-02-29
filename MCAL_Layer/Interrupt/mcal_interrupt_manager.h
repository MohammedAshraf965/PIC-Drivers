/* 
 * File:   mcal_interrupt_manager.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:28
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/* Section: Includes */

#include "mcal_interrupt_config.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(void);
void RB5_ISR(void);
void RB6_ISR(void);
void RB7_ISR(void);

void ADC_ISR(void);

void TMR0_ISR(void);

#endif	/* MCAL_INTERRUPT_MANAGER_H */

