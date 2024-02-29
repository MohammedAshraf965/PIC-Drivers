/* 
 * File:   hal_timer0.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/11, 12:40
 */

/************************** Section: Includes **************************/

#include "hal_timer0.h"

/************************** Section: Macro Declarations **************************/

/************************** Section: Function Function Declarations **************************/

static inline void Timer0_Prescaler_Config(const Timer0_t *_timer);
static inline void Timer0_Mode_Select(const Timer0_t *_timer);
static inline void Timer0_Register_Config(const Timer0_t *_timer);

/************************** Section: Data Type Declarations **************************/

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        static TMR0_InterruptHandler TIMER0_InterruptHandler = NULL;
#endif

static uint16 timer0_preload_value = 0;
        
/************************** Section: Function Definitions **************************/

Std_ReturnType Timer0_Init(const Timer0_t *_timer)
{
    Std_ReturnType ret = E_NOK;
    
    if(_timer == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable Timer0 */
        TIMER0_CONFIG_DISABLE();
        //T0CONbits.TMR0ON = 0;
        
        /* Set Timer0 Prescaler */
        Timer0_Prescaler_Config(_timer);
        
        /* Set Timer0 Mode */
        Timer0_Mode_Select(_timer);
        
        /* Set Timer0 Register Configuration */
        Timer0_Register_Config(_timer);
        
        /* Load preloaded value into the registers */
        TMR0H = (_timer -> preload_value) >> 8;
        TMR0L = _timer -> preload_value;
        timer0_preload_value = _timer -> preload_value;
        
        /* Set Timer0 Interrupt Mode (if applicable) */
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

        if(_timer -> priority == INTERRUPT_HIGH_PRIORITY)
        {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_HighPrioritySet();
        }
        else if(_timer -> priority == INTERRUPT_LOW_PRIORITY)
        {
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_LowPrioritySet();
        }
        else {/* Nothing */}
        
        #else
        
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        
        #endif
        
        TIMER0_InterruptHandler = _timer -> TIMER0_InterruptHandler;
        
        #endif
        
        /* Enable Timer0 */
        TIMER0_CONFIG_ENABLE();
        
        ret = E_OK;
    }
     
    return ret;
}

Std_ReturnType Timer0_DeInit(const Timer0_t *_timer)
{
    Std_ReturnType ret = E_NOK;
    
    if(_timer == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        TIMER0_CONFIG_DISABLE();
        
        #if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_InterruptDisable();
        #endif    
    }
    
    return ret;
}

Std_ReturnType Timer0_Read_Value(const Timer0_t *_timer, uint16 *value)
{
    Std_ReturnType ret = E_NOK;
    uint8 tmr0_low = 0, tmr0_high = 0;
    
    if((_timer == NULL) || (value == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        tmr0_low = TMR0L;
        tmr0_high = TMR0H;
        *value = (uint16)(tmr0_high << 8) + tmr0_low;
        ret = E_OK;
    }  
    
    return ret;
}

Std_ReturnType Timer0_Write_Value(const Timer0_t *_timer, uint16 value)
{
    Std_ReturnType ret = E_NOK;
    
    if(_timer == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        TMR0H = value >> 8;
        TMR0L = value;
    }
    
    return ret;
}

void TMR0_ISR(void)
{
    TIMER0_InterruptFlagClear();
    
    TMR0H = timer0_preload_value >> 8;
    TMR0L = timer0_preload_value;
    
    if(TIMER0_InterruptHandler)
    {
        TIMER0_InterruptHandler();
    }
    else
    {
        
    }
    
}

static inline void Timer0_Prescaler_Config(const Timer0_t *_timer)
{
    if(_timer -> prescaler_status == TIMER0_PRESCALER_ENABLE_CFG)
    {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = _timer -> prescaler_val;
    }
    else if(_timer -> prescaler_status == TIMER0_PRESCALER_DISABLE_CFG)
    {
        TIMER0_PRESCALER_DISABLE();
    }
    else {/* Nothing */}
}

static inline void Timer0_Mode_Select(const Timer0_t *_timer)
{
    if(_timer -> prescaler_status == TIMER0_TIMER_MODE_CFG)
    {
        TIMER0_CLOCK_TIMER_MODE();
    }
    else if(_timer -> prescaler_status == TIMER0_COUNTER_MODE_CFG)
    {
        TIMER0_CLOCK_COUNTER_MODE();
        
        if(_timer -> timer0_counter_edge == TIMER0_RISING_EDGE_CFG)
        {
            TIMER0_INCREMENT_ON_RISINNG_EDGE();
        }
        else if(_timer -> timer0_counter_edge == TIMER0_FALLING_EDGE_CFG)
        {
            TIMER0_INCREMENT_ON_FALLING_EDGE();
        }
        else {/* Nothing */}
    }
    else {/* Nothing */}
}

static inline void Timer0_Register_Config(const Timer0_t *_timer)
{
    if(_timer -> timer0_register_size == TIMER0_8BIT_MODE)
    {
        TIMER0_8BIT_CONFIG();
    }
    else if(_timer -> prescaler_status == TIMER0_16BIT_MODE)
    {
        TIMER0_16BIT_CONFIG();
    }
    else {/* Nothing */}
}