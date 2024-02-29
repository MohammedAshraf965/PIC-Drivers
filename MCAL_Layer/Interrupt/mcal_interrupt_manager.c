/* 
 * File:   mcal_interrupt_manager.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:28
 */

/* Section: Includes */

#include "mcal_interrupt_manager.h"

/* Section: Macro Declarations */

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Definitions */

/*
//#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
void __interrupt InterruptManagerHigh(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_TRIGERRED))
    {
      INT0_ISR();
    }
    else {}

    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_TRIGERRED))
  {
      INT2_ISR();
  }
  else {}
}

void __interrupt(low_priority) InterruptManagerLow(void)
{
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_TRIGERRED))
  {
      INT1_ISR();
  }
  else {}
}

//#else
*/

void __interrupt() InterruptManager(void)
{
    if((INTCONbits.INT0IE == INTERRUPT_ENABLE) && (INTCONbits.INT0IF == INTERRUPT_TRIGERRED))
    {
      INT0_ISR();
    }
    else {/* Nothing */}
  
    if((INTCON3bits.INT1IE == INTERRUPT_ENABLE) && (INTCON3bits.INT1IF == INTERRUPT_TRIGERRED))
    {
      INT1_ISR();
    }
    else {/* Nothing */}
  
    if((INTCON3bits.INT2IE == INTERRUPT_ENABLE) && (INTCON3bits.INT2IF == INTERRUPT_TRIGERRED))
    {
      INT2_ISR();
    }
    else {/* Nothing */}
  
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_TRIGERRED) && (PORTBbits.RB4 == GPIO_HIGH))
    {
      RB4_ISR();
    }
    else {/* Nothing */}
  
      if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_TRIGERRED) && (PORTBbits.RB4 == GPIO_LOW))
    {
      RB4_ISR();
    }
    else {/* Nothing */}
  
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_TRIGERRED))
    {
      RB5_ISR();
    }
    else {/* Nothing */}
  
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_TRIGERRED))
    {
      RB6_ISR();
    }
    else {/* Nothing */}
  
    if((INTCONbits.RBIE == INTERRUPT_ENABLE) && (INTCONbits.RBIF == INTERRUPT_TRIGERRED))
    {
      RB7_ISR();
    }
    else {/* Nothing */}
  
    if((PIE1bits.ADIE == INTERRUPT_ENABLE) && (PIR1bits.ADIF == INTERRUPT_TRIGERRED))
    {
      ADC_ISR();
    }
    else {/* Nothing */}
  
    if((INTCONbits.TMR0IE == INTERRUPT_ENABLE) && (INTCONbits.TMR0IF == INTERRUPT_TRIGERRED))
    {
      TMR0_ISR();
    }
    else {/* Nothing */}
}

//#endif