/* 
 * File:   mcal_external_interrupt.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:27
 */

/************************** Section: Includes **************************/

#include "mcal_external_interrupt.h"

/************************** Section: Function Declarations **************************/
InterruptHandler INT0_InterruptHandler = NULL;
InterruptHandler INT1_InterruptHandler = NULL;
InterruptHandler INT2_InterruptHandler = NULL;

InterruptHandler RB4_InterruptHandler = NULL;
InterruptHandler RB5_InterruptHandler = NULL;
InterruptHandler RB6_InterruptHandler = NULL;
InterruptHandler RB7_InterruptHandler = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (*Interrupt_Handler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (*Interrupt_Handler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (*Interrupt_Handler)(void));
static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Interrupt_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj);

/************************** Section: Function Definitions **************************/

/**
 * @brief Initialize the INTx interrupt
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType interrupt_INTx_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable the External Interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear the Interrupt Flag: External Interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        /* Configure the External Interrupt Edge */
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        /* Configure the External Interrupt Priority */
        ret |= Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure the External Interrupt I/O */
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        /* Configure the Default Interrupt Callback */
        ret |= INTx_SetInterruptHandler(int_obj);
        /* Enable the External Interrupt */
        ret |= Interrupt_INTx_Enable(int_obj);
    }
    
    return ret;   
}

/**
 * @brief Deinitialize the INTx interrupt
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = Interrupt_INTx_Disable(int_obj);
    }
    
    return ret;
}


/**
 * @brief Enable the INTx interrupt
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                
                INTERRUPT_GlobalInterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
                
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if(int_obj -> priority == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(int_obj -> priority == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else {/* Nothing */}
#else
            /* Enable all global interrupts  */
            INTERRUPT_GlobalInterruptEnable();
            /* Enable all peripheral interrupts  */
            INTERRUPT_PeripheralInterruptEnable();
#endif                
                EXT_INT1_InterruptEnable();
                ret = E_OK; 
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_InterruptPriorityEnable();
                if(int_obj -> priority == INTERRUPT_LOW_PRIORITY)
                {
                    INTERRUPT_GlobalInterruptLowEnable();
                }
                else if(int_obj -> priority == INTERRUPT_HIGH_PRIORITY)
                {
                    INTERRUPT_GlobalInterruptHighEnable();
                }
                else {/* Nothing */}
#else
            /* Enable all global interrupts  */
            INTERRUPT_GlobalInterruptEnable();
            /* Enable all peripheral interrupts  */
            INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_InterruptEnable();
                ret = E_OK; 
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;
}

/**
 * @brief Disable the INTx interrupt
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0: 
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
                
            case INTERRUPT_EXTERNAL_INT1: 
                EXT_INT1_InterruptDisable();
                ret = E_OK; 
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
                EXT_INT2_InterruptDisable();
                ret = E_OK; 
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;
}

/**
 * @brief Configures the INTx interrupt priority
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {       
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj -> priority == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT1_LowPrioritySet();
                }
                else if(int_obj -> priority == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT1_HighPrioritySet();
                }
                else {/* Nothing */}
                ret = E_OK; 
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
                if(int_obj -> priority == INTERRUPT_LOW_PRIORITY)
                {
                    EXT_INT2_LowPrioritySet();
                }
                else if(int_obj -> priority == INTERRUPT_HIGH_PRIORITY)
                {
                    EXT_INT2_HighPrioritySet();
                }
                else {/* Nothing */}
                ret = E_OK; 
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;
}
#endif

/**
 * @brief Configures the INTx interrupt on rising or falling edge
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0: 
                if(int_obj -> edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT0_INT0_Falling_Edge();
                }
                else if(int_obj -> edge == INTERRUPT_RISING_EDGE)
                {
                    EXT0_INT0_Rising_Edge();
                }
                else {/* Nothing */}
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT1:
                if(int_obj -> edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT1_Falling_Edge();
                }
                else if(int_obj -> edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT1_Rising_Edge();
                }
                else {/* Nothing */}
                ret = E_OK; 
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
                if(int_obj -> edge == INTERRUPT_FALLING_EDGE)
                {
                    EXT_INT2_Falling_Edge();
                }
                else if(int_obj -> edge == INTERRUPT_RISING_EDGE)
                {
                    EXT_INT2_Rising_Edge();
                }
                else {/* Nothing */}
                ret = E_OK; 
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;
}

/**
 * @brief Initialize the INTx interrupt pin
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(int_obj -> mcu_pin));
    }
    
    return ret;
}

/**
 * @brief Clear the INTx interrupt flag
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0: 
                EXT_INT0_InterruptFlagClear();
                ret = E_OK;
                break;
                
            case INTERRUPT_EXTERNAL_INT1: 
                EXT_INT1_InterruptFlagClear();
                ret = E_OK; 
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
                EXT_INT2_InterruptFlagClear();
                ret = E_OK; 
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;   
}

/**
 * @brief Initialize the INT0 interrupt handler
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType INT0_SetInterruptHandler(void (*Interrupt_Handler)(void))
{
    Std_ReturnType ret = E_OK;
    
    if(Interrupt_Handler == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        INT0_InterruptHandler = Interrupt_Handler;
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Initialize the INT1 interrupt handler 
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType INT1_SetInterruptHandler(void (*Interrupt_Handler)(void))
{
    Std_ReturnType ret = E_OK;
    
    if(Interrupt_Handler == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        INT1_InterruptHandler = Interrupt_Handler;
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Initialize the INT2 interrupt handler
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType INT2_SetInterruptHandler(void (*Interrupt_Handler)(void))
{
    Std_ReturnType ret = E_OK;
    
    if(Interrupt_Handler == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        INT2_InterruptHandler = Interrupt_Handler;
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Initialize the INTx interrupt handler
 * @param int_obj pointer to the INTx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(int_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        switch(int_obj -> source)
        {
            case INTERRUPT_EXTERNAL_INT0: 
                ret = INT0_SetInterruptHandler(int_obj -> EXT_InterruptHandler);
                break;
                
            case INTERRUPT_EXTERNAL_INT1: 
                ret = INT1_SetInterruptHandler(int_obj -> EXT_InterruptHandler);
                break;
                
            case INTERRUPT_EXTERNAL_INT2: 
                ret = INT2_SetInterruptHandler(int_obj -> EXT_InterruptHandler);
                break;
                
            default : 
                ret = E_NOK; 
                break;
        }
    }
    
    return ret;     
}

void INT0_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_INT0_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_INT1_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_INT2_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}


/**
 * @brief Initialize the RBx interrupt
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType interrupt_RBx_Init(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_OK;
    
    if(rb_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable the external interrupts RBx */
        ret = interrupt_RBx_DeInit(rb_obj);
        
        /* Clears the flag of the external interrupts RBx */
        ret = Interrupt_RBx_Clear_Flag(rb_obj);
        
        /* Initialize the External Interrupt */
        ret = Interrupt_RBx_Interrupt_Init(rb_obj);
        
        /* Configure the External Interrupt I/O */
        ret = Interrupt_RBx_Pin_Init(rb_obj);
       
        /* Configure the Default Interrupt Callback */
        switch(rb_obj -> mcu_pin.pin)
        {
            case GPIO_PIN4:
                RB4_InterruptHandler = rb_obj -> EXT_InterruptHandler;
                ret = E_OK;
                break;
            case GPIO_PIN5:
                RB5_InterruptHandler = rb_obj -> EXT_InterruptHandler;
                ret = E_OK;
                break;
            case GPIO_PIN6:
                RB6_InterruptHandler = rb_obj -> EXT_InterruptHandler;
                ret = E_OK;
                break;
            case GPIO_PIN7:
                RB7_InterruptHandler = rb_obj -> EXT_InterruptHandler;
                ret = E_OK;
                break;
            default:
                ret = E_NOK;
                break;
        }
        
        /* Enable the External Interrupt */
        ret = Interrupt_RBx_Enable(rb_obj);
    }
    
    return ret;  
}

/**
 * @brief Deinitialize the RBx interrupt 
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType interrupt_RBx_DeInit(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(rb_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        EXT_RBx_InterruptDisable();
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Enable the RBx interrupt
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    EXT_RBx_InterruptEnable();
    ret = E_OK;
    
    return ret;
}

/**
 * @brief Disable the RBx interrupt
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    EXT_RBx_InterruptDisable();
    ret = E_OK;
    
    return ret;  
}

/**
 * @brief Configure the RBx interrupt priority
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */

static Std_ReturnType Interrupt_RBx_Interrupt_Init(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

        INTERRUPT_InterruptPriorityEnable();
        
        if(rb_obj -> priority == INTERRUPT_LOW_PRIORITY)
        {
            /* Enable all low priority interrupts  */
            INTERRUPT_GlobalInterruptLowEnable();
            
            /* Enable the external interrupts RBx priority to be low priority */
            EXT_RBx_InterruptLowPriority();
            
            ret = E_OK;
        }
        else if(rb_obj -> priority == INTERRUPT_HIGH_PRIORITY)
        {
            /* Enable all high priority interrupts  */
            INTERRUPT_GlobalInterruptHighEnable();
            
            /* Enable the external interrupts RBx priority to be high priority */
            EXT_RBx_InterruptHighPriority();
            
            ret = E_OK;
        }
        else {/* Nothing */}
    #else

        /* Enable all global interrupts  */
        INTERRUPT_GlobalInterruptEnable();
        
        /* Enable all peripheral interrupts  */
        INTERRUPT_PeripheralInterruptEnable();
        
        ret = E_OK;
        
    #endif
       
        return ret;
}

/**
 * @brief Initialize the RBx interrupt pin
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(rb_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = gpio_pin_direction_initialize(&(rb_obj -> mcu_pin));
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Clear the RBx interrupt flag
 * @param rb_obj pointer to the RBx interrupt configuration
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
static Std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *rb_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(rb_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        EXT_RBx_InterruptFlagClear();
        ret = E_OK;    
    }
    
    return ret;  
}

void RB4_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(RB4_InterruptHandler)
    {
        RB4_InterruptHandler();
    }
}

void RB5_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(RB5_InterruptHandler)
    {
        RB5_InterruptHandler();
    }
}

void RB6_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(RB6_InterruptHandler)
    {
        RB6_InterruptHandler();
    }
}

void RB7_ISR(void)
{
    /* Clear the Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    
    /* Execute Code */
    
    /* Return back to the Callback function */
    if(RB7_InterruptHandler)
    {
        RB7_InterruptHandler();
    }
}