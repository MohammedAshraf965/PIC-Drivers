/* 
 * File:   ecu_layer_init.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/08, 10:31
 */

/* Section: Includes */

#include "ecu_layer_init.h"

/* Section: Macro Declarations */


/* Section: Macro Function Declarations */


/* Section: Data Type Declarations */

adc_conf_t adc_1 = 
{
  //.ADC_InterruptHandler = ADC_DefaultInterrupt,
  .acquisition_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
  .acquisiton_time = ADC_12_TAD,
  .adc_channel_pin = ADC_CHANNEL_AN0,
  .result_format = ADC_RESULT_RIGHT_CONFIGURATION,
  .voltage_ref = ADC_CLEAR_VREF
};

keypad_t keypad_1 =
{
  .keypad_row_pins[0].port          = PORTC_INDEX,
  .keypad_row_pins[0].pin           = GPIO_PIN0,
  .keypad_row_pins[0].direction     = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[0].logic         = GPIO_LOW,
  .keypad_row_pins[1].port          = PORTC_INDEX,
  .keypad_row_pins[1].pin           = GPIO_PIN1,
  .keypad_row_pins[1].direction     = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[1].logic         = GPIO_LOW,
  .keypad_row_pins[2].port          = PORTC_INDEX,
  .keypad_row_pins[2].pin           = GPIO_PIN2,
  .keypad_row_pins[2].direction     = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[2].logic         = GPIO_LOW,
  .keypad_row_pins[3].port          = PORTC_INDEX,
  .keypad_row_pins[3].pin           = GPIO_PIN3,
  .keypad_row_pins[3].direction     = GPIO_DIRECTION_OUTPUT,
  .keypad_row_pins[3].logic         = GPIO_LOW,
  
  .keypad_column_pins[0].port       = PORTC_INDEX,
  .keypad_column_pins[0].pin        = GPIO_PIN4,
  .keypad_column_pins[0].direction  = GPIO_DIRECTION_INPUT,
  .keypad_column_pins[0].logic      = GPIO_LOW,
  .keypad_column_pins[1].port       = PORTC_INDEX,
  .keypad_column_pins[1].pin        = GPIO_PIN5,
  .keypad_column_pins[1].direction  = GPIO_DIRECTION_INPUT,
  .keypad_column_pins[1].logic      = GPIO_LOW,
  .keypad_column_pins[2].port       = PORTC_INDEX,
  .keypad_column_pins[2].pin        = GPIO_PIN6,
  .keypad_column_pins[2].direction  = GPIO_DIRECTION_INPUT,
  .keypad_column_pins[2].logic      = GPIO_LOW,
  .keypad_column_pins[3].port       = PORTC_INDEX,
  .keypad_column_pins[3].pin        = GPIO_PIN7,
  .keypad_column_pins[3].direction  = GPIO_DIRECTION_INPUT,
  .keypad_column_pins[3].logic      = GPIO_LOW,
};

chr_lcd_4bit_t lcd_4bit =
{
  .lcd_rs.port =                 PORTC_INDEX,
  .lcd_rs.pin =                  GPIO_PIN0,
  .lcd_rs.direction =            GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic =                GPIO_LOW,
  
  .lcd_en.port =                 PORTC_INDEX,
  .lcd_en.pin =                  GPIO_PIN1,
  .lcd_en.direction =            GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic =                GPIO_LOW,
  
  .lcd_data[0].port =            PORTC_INDEX,
  .lcd_data[0].pin =             GPIO_PIN2,
  .lcd_data[0].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic =           GPIO_LOW,
  
  .lcd_data[1].port =            PORTC_INDEX,
  .lcd_data[1].pin =             GPIO_PIN3,
  .lcd_data[1].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic =           GPIO_LOW,
  
  .lcd_data[2].port =            PORTC_INDEX,
  .lcd_data[2].pin =             GPIO_PIN4,
  .lcd_data[2].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic =           GPIO_LOW,
  
  .lcd_data[3].port =            PORTC_INDEX,
  .lcd_data[3].pin =             GPIO_PIN5,
  .lcd_data[3].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic =           GPIO_LOW,
};

chr_lcd_8bit_t lcd_8bit =
{
  .lcd_rs.port =                 PORTC_INDEX,
  .lcd_rs.pin =                  GPIO_PIN6,
  .lcd_rs.direction =            GPIO_DIRECTION_OUTPUT,
  .lcd_rs.logic =                GPIO_LOW,
  
  .lcd_en.port =                 PORTC_INDEX,
  .lcd_en.pin =                  GPIO_PIN7,
  .lcd_en.direction =            GPIO_DIRECTION_OUTPUT,
  .lcd_en.logic =                GPIO_LOW,
  
  .lcd_data[0].port =            PORTD_INDEX,
  .lcd_data[0].pin =             GPIO_PIN0,
  .lcd_data[0].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[0].logic =           GPIO_LOW,
  
  .lcd_data[1].port =            PORTD_INDEX,
  .lcd_data[1].pin =             GPIO_PIN1,
  .lcd_data[1].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[1].logic =           GPIO_LOW,
  
  .lcd_data[2].port =            PORTD_INDEX,
  .lcd_data[2].pin =             GPIO_PIN2,
  .lcd_data[2].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[2].logic =           GPIO_LOW,
  
  .lcd_data[3].port =            PORTD_INDEX,
  .lcd_data[3].pin =             GPIO_PIN3,
  .lcd_data[3].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[3].logic =           GPIO_LOW,
  
  .lcd_data[4].port =            PORTD_INDEX,
  .lcd_data[4].pin =             GPIO_PIN4,
  .lcd_data[4].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[4].logic =           GPIO_LOW,
  
  .lcd_data[5].port =            PORTD_INDEX,
  .lcd_data[5].pin =             GPIO_PIN5,
  .lcd_data[5].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[5].logic =           GPIO_LOW,
  
  .lcd_data[6].port =            PORTD_INDEX,
  .lcd_data[6].pin =             GPIO_PIN6,
  .lcd_data[6].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[6].logic =           GPIO_LOW,
  
  .lcd_data[7].port =            PORTD_INDEX,
  .lcd_data[7].pin =             GPIO_PIN7,
  .lcd_data[7].direction =       GPIO_DIRECTION_OUTPUT,
  .lcd_data[7].logic =           GPIO_LOW,
};

usart_t usart_obj =
{
  .baudrate = 9600,
  .baudrate_gen_config = BAUDRATE_ASYN_8BIT_LOW_SPEED,
  
  .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
  .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE,
  .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE,
  
  .usart_rx_cfg.usart_rx_enable = EUSART_ASYNCHRONOUS_RX_ENABLE,
  .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE,
  .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE,
  
  .EUSART_TxDefaultInterruptHandler = NULL,
  .EUSART_RxDefaultInterruptHandler = NULL,
  .EUSART_FramingErrorHandler = NULL,
  .EUSART_OverrunErrorHandler = NULL
};

Std_ReturnType ret = E_NOK;

/* Section: Function Definitions */

void ecu_layer_init(void)
{
    //ret = Keypad_Initialize(&keypad_1);
    //ret = lcd_4bit_initialize(&lcd_4bit);
    //ret = lcd_8bit_initialize(&lcd_8bit);
    ret = EUSART_Init(&usart_obj);
}