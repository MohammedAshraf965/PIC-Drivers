/* 
 * File:   hal_adc.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/07, 10:51
 */

/************************** Section: Includes **************************/

#include "hal_adc.h"

/************************** Section: Function Declarations **************************/

static inline void ADC_Input_Channel_Port_Configure(adc_channel_pin_t channel);
static inline void ADC_Select_Result_Format(const adc_conf_t *adc_obj);
static inline void ADC_Set_Voltage_Mode(const adc_conf_t *adc_obj);

/************************** Section: Macro Function Declarations **************************/

/************************** Section: Data Type Declarations **************************/

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static ADCInterruptHandler ADC_InterruptHandler = NULL;
#endif

/************************** Section: Function Definitions **************************/

/**
 * @brief Initializes the ADC
 * @param adc_obj Pointer to the ADC configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_Init(const adc_conf_t *adc_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(adc_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable the ADC */
        ADC_MODULE_DISABLE();
        
        /* Configure the acquisition time */
        ADCON2bits.ACQT = adc_obj -> acquisiton_time;
        
        /* Configure the conversion clock */
        ADCON2bits.ADCS = adc_obj -> acquisition_clock;
        
        /* Configure the default channel */
        ADCON0bits.CHS = adc_obj -> adc_channel_pin;
        ADC_Input_Channel_Port_Configure(adc_obj -> adc_channel_pin);
        
        /* Configure the interrupt */
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
        ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        if(adc_obj -> priority == INTERRUPT_HIGH_PRIORITY)
        {
            ADC_HighPrioritySet();
        }
        else if(adc_obj -> priority == INTERRUPT_LOW_PRIORITY)
        {
            ADC_LowPrioritySet();
        }
        else {/* Nothing */}
#endif
        ADC_InterruptHandler = adc_obj -> ADC_InterruptHandler;
#endif
        
        /* Configure the result format */
        ADC_Select_Result_Format(adc_obj);
        
        /* Configure the voltage reference */
        ADC_Set_Voltage_Mode(adc_obj);
        
        /* Enable the ADC */
        ADC_MODULE_ENABLE();
        
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Deinitializes the ADC
 * @param adc_obj Pointer to the ADC configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_DeInit(const adc_conf_t *adc_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(adc_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Disable the ADC */
        ADC_MODULE_DISABLE();
        /* Disable the ADC interrupt */
        ADC_InterruptDisable();
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Select the specified ADC channel
 * @param adc_obj Pointer to the ADC configurations
 * @param channel ADC channel to be selected
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_Select_Channel(const adc_conf_t *adc_obj, adc_channel_pin_t channel)
{
    Std_ReturnType ret = E_NOK;
    
    if(adc_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Configure the default channel */
        ADCON0bits.CHS = channel;
        ADC_Input_Channel_Port_Configure(channel);
        ret = E_OK;
    }
    
    return ret; 
}

/**
 * @brief Starts the ADC conversion process
 * @param adc_obj Pointer to the ADC configurations
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *adc_obj)
{
    Std_ReturnType ret = E_NOK;
    
    if(adc_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ADC_START_CONVERSION();
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Verify the ADC conversion completion
 * @param adc_obj Pointer to the ADC configurations
 * @param conversion_status Status of the ADC conversion process
 *                      true: The conversion is complete
 *                      false: The conversion is not yet completed
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *adc_obj, uint8 *conversion_status)
{
    Std_ReturnType ret = E_NOK;
    
    if((adc_obj == NULL) || (conversion_status == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        *conversion_status = (uint8)(!(ADC_CONVERSION_STATUS()));
        ret = E_OK;
    }
    
    return ret; 
}

/**
 * @brief Returns the ADC conversion results
 * @param adc_obj Pointer to the ADC configurations
 * @param conversion_result Result of the ADC conversion process
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *adc_obj, adc_result *conversion_result)
{
    Std_ReturnType ret = E_NOK;
    
    if((adc_obj == NULL) || (conversion_result == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        if(adc_obj -> result_format == ADC_RESULT_RIGHT_CONFIGURATION)
        {
            *conversion_result = (adc_result)((ADRESH << 8) + ADRESL);
        }
        else if(adc_obj -> result_format == ADC_RESULT_LEFT_CONFIGURATION)
        {
            *conversion_result = (adc_result)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else
        {
            *conversion_result = (adc_result)((ADRESH << 8) + ADRESL);
        }
        
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief Configures and returns the result of the ADC conversion
 * @param adc_obj Pointer to the ADC configurations
 * @param channel ADC channel to be selected
 * @param conversion_result Result of the ADC conversion process
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_GetConversion(const adc_conf_t *adc_obj, adc_channel_pin_t channel, adc_result *conversion_result)
{
    Std_ReturnType ret = E_NOK;
    uint8 conversion_status = ZERO;
    
    if((adc_obj == NULL) || (conversion_result == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        /* Select the A/D channel */
        ret |= ADC_Select_Channel(adc_obj, channel);
        
        /* Select the A/D conversion */
        ret |= ADC_Start_Conversion(adc_obj);
        
        /* Check if the conversion is done */
        ret |= ADC_IsConversionDone(adc_obj, &conversion_status);
        
        /* Wait until the conversion is complete */
        while(ADCON0bits.GO_nDONE);
        ret |= ADC_GetConversionResult(adc_obj, conversion_result);
    }
    
    return ret; 
}

/**
 * @brief Configures and returns the result of the ADC conversion
 * @param adc_obj Pointer to the ADC configurations
 * @param channel ADC channel to be selected
 * @param conversion_result Result of the ADC conversion process
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc_obj, adc_channel_pin_t channel)
{
    Std_ReturnType ret = E_NOK;
    
    if(adc_obj == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Select the A/D channel */
        ret |= ADC_Select_Channel(adc_obj, channel);
        
        /* Select the A/D conversion */
        ret |= ADC_Start_Conversion(adc_obj);
    }
    
    return ret; 
}

static inline void ADC_Input_Channel_Port_Configure(adc_channel_pin_t channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_AN0:
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3:
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11:
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12:
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        default:
            break;
    }
    
}

static inline void ADC_Select_Result_Format(const adc_conf_t *adc_obj)
{
    switch(adc_obj -> result_format)
    {
        case ADC_RESULT_RIGHT_CONFIGURATION:
            ADC_RESULT_RIGHT_FORMAT();
            break;
        case ADC_RESULT_LEFT_CONFIGURATION:
            ADC_RESULT_LEFT_FORMAT();
            break;
        default:
            ADC_RESULT_RIGHT_FORMAT();
            break;
    }
}

static inline void ADC_Set_Voltage_Mode(const adc_conf_t *adc_obj)
{
    switch(adc_obj -> voltage_ref)
    {
        case ADC_SET_VREF:
            ADC_ENABLE_VREF();
            break;
        case ADC_CLEAR_VREF:
            ADC_DISABLE_VREF();
            break;
        default:
            ADC_DISABLE_VREF();
            break;
    }
}

void ADC_ISR(void)
{
    ADC_InterruptFlagClear();
    
    if(ADC_InterruptHandler)
    {
        ADC_InterruptHandler();
    }
    else
    {
        
    }
    
}