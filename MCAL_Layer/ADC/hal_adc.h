/* 
 * File:   hal_adc.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/07, 10:51
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/************************** Section: Includes **************************/

#include "xc.h"
#include "hal_adc_config.h"
#include "../GPIO/hal_gpio.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/************************** Section: Macro Declarations **************************/

#define ADC_AN0_ANALOG_FUNCTIONALITY                0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY                0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY                0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY                0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY                0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY                0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY                0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY                0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY                0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY                0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY               0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY               0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY               0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY                0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY               0x0F

#define ADC_RESULT_RIGHT_CONFIGURATION              0x01
#define ADC_RESULT_LEFT_CONFIGURATION               0x00

#define ADC_SET_VREF                                0x01
#define ADC_CLEAR_VREF                              0x00

#define ADC_CONVERSION_COMPLETED                    0x01
#define ADC_CONVERSION_INPROGRESS                   0x00

/************************** Section: Macro Function Declarations **************************/

/* Notify the ADC conversion status" A/D conversion in progress / A/D idle*/
#define ADC_CONVERSION_STATUS()                  (ADCON0bits.GO_nDONE)

/* Start the A/D conversion */
#define ADC_START_CONVERSION()                   (ADCON0bits.GODONE = 1)

/* Enable or disable the ADC */

#define ADC_MODULE_ENABLE()                      (ADCON0bits.ADON = 1)
#define ADC_MODULE_DISABLE()                     (ADCON0bits.ADON = 0)

/* Enable or Disable the use of VREF for ADC */
#define ADC_ENABLE_VREF()                         do{ADCON1bits.VCFG1 = 1;\
                                                     ADCON1bits.VCFG0 = 1;\
                                                    }while(0)

#define ADC_DISABLE_VREF()                         do{ADCON1bits.VCFG1 = 0;\
                                                      ADCON1bits.VCFG0 = 0;\
                                                    }while(0)

/* Configure ADC bits to be Analogue or Digital */
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)   (ADCON1bits.PCFG = _CONFIG)

/* ADC Result Format Select */
#define ADC_RESULT_RIGHT_FORMAT()                 (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()                  (ADCON2bits.ADFM = 0)

/************************** Section: Data Type Declarations **************************/

/*
 * ?brief ADC Channel Pins definition
 */
typedef enum
{
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12       
}adc_channel_pin_t;

typedef enum
{
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef enum
{
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,        
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,        
}adc_conversion_clock_t;

typedef struct
{
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);        /* Pointer to function for upper layers */
    interrupt_priority_config priority;
#endif
    adc_acquisition_time_t acquisiton_time;     /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t acquisition_clock;   /* @ref adc_conversion_clock_t */
    adc_channel_pin_t      adc_channel_pin;     /* @ref adc_channel_pin */
    uint8 voltage_ref      :1;                  /* Voltage Reference Configuration */
    uint8 result_format    :1;                  /* A/D Result Format Select */
    uint8 ADC_Reserved     :6;
}adc_conf_t;

typedef uint16 adc_result;
/************************** Section: Function Declarations **************************/

Std_ReturnType ADC_Init(const adc_conf_t *adc_obj);
Std_ReturnType ADC_DeInit(const adc_conf_t *adc_obj);
Std_ReturnType ADC_Select_Channel(const adc_conf_t *adc_obj, adc_channel_pin_t channel);
Std_ReturnType ADC_Start_Conversion(const adc_conf_t *adc_obj);
Std_ReturnType ADC_IsConversionDone(const adc_conf_t *adc_obj, uint8 *conversion_status);
Std_ReturnType ADC_GetConversionResult(const adc_conf_t *adc_obj, adc_result *conversion_result);
Std_ReturnType ADC_GetConversion(const adc_conf_t *adc_obj, adc_channel_pin_t channel, adc_result *conversion_result);
Std_ReturnType ADC_StartConversion_Interrupt(const adc_conf_t *adc_obj, adc_channel_pin_t channel);

#endif	/* HAL_ADC_H */

