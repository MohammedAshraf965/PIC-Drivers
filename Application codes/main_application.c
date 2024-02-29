/* 
 * File:   application.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:18
 */


/* Section: Includes */

#include "application.h"

/* Section: Function Declarations */
void INT0_ISR_APP(void);

/* Section: Main Application */
/*
pin_config_t Pin_1 =
{
    .port = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW   
};

pin_config_t btn_1 =
{
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .direction = GPIO_DIRECTION_INPUT,
    .logic = GPIO_LOW   
};
*/
/************* LED and Button Example *************/

led_t LED_1 =
{
    .portname = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

/*
button_t BTN_1 = 
{
    .button_pin.port = PORTC_INDEX,
    .button_pin.pin = GPIO_PIN2,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_LOW,
    .button_state = BUTTON_RELEASED,
    .button_connection = BUTTON_ACTIVE_HIGH,
};

button_t BTN_2 = 
{
    .button_pin.port = PORTD_INDEX,
    .button_pin.pin = GPIO_PIN0,
    .button_pin.direction = GPIO_DIRECTION_INPUT,
    .button_pin.logic = GPIO_HIGH,
    .button_state = BUTTON_RELEASED,
    .button_connection = BUTTON_ACTIVE_LOW,
};

*/

/************* Relay Example *************/
/*
relay_t Relay_1 =
{
    .relay_port = PORTC_INDEX,
    .relay_pin = GPIO_PIN0,
    .relay_status = RELAY_OFF_STATUS
};
*/
/************* DC Motor Example *************/
/*
dc_motor_t DC_Motor_1 = 
{
    .dc_motor_pin[0].port = PORTC_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN0,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = GPIO_LOW,
    .dc_motor_pin[1].port = PORTC_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN1,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = GPIO_LOW
};

dc_motor_t DC_Motor_2 = 
{
    .dc_motor_pin[0].port = PORTC_INDEX,
    .dc_motor_pin[0].pin = GPIO_PIN2,
    .dc_motor_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[0].logic = GPIO_LOW,
    .dc_motor_pin[1].port = PORTC_INDEX,
    .dc_motor_pin[1].pin = GPIO_PIN3,
    .dc_motor_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor_pin[1].logic = GPIO_LOW
};
*/

/************* Seven Segment Example *************/
/*
seven_segment_t seg_1 = 
{
    .segment_pins[0].port = PORTC_INDEX,
    .segment_pins[0].pin = GPIO_PIN0,
    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[0].logic = GPIO_LOW,
    
    .segment_pins[1].port = PORTC_INDEX,
    .segment_pins[1].pin = GPIO_PIN1,
    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[1].logic = GPIO_LOW,
    
    .segment_pins[2].port = PORTC_INDEX,
    .segment_pins[2].pin = GPIO_PIN2,
    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[2].logic = GPIO_LOW,
    
    .segment_pins[3].port = PORTC_INDEX,
    .segment_pins[3].pin = GPIO_PIN3,
    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .segment_pins[3].logic = GPIO_LOW,
    
    .segment_type = SEGMENT_COMMON_ANODE
};
*/

interrupt_INTx_t INT0_obj =
{
    .EXT_InterruptHandler = INT0_ISR_APP,
    .edge = INTERRUPT_FALLING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};
/*
button_state_t btn1_status;
button_state_t btn2_status;
direction_t led1_st;
logic_t btn1_st;
uint8 portc_st;
*/

Std_ReturnType ret = E_NOK;

int main()
{   
    application_initialize();

    while(1)
    {  
        /************* LED and Button Example *************/
        /*
        button_read(&BTN_1, &btn1_status);
        button_read(&BTN_2, &btn2_status);
        
        if(btn1_status == BUTTON_PRESSED)
        {
            led_switch_on(&LED_1);
        }
        else
        {
            led_switch_off(&LED_1);
        }
        
        if(btn2_status == BUTTON_PRESSED)
        {
            led_switch_on(&LED_1);
        }
        else
        {
            led_switch_off  (&LED_1);
        }
        */
        
        /************* Relay Example *************/
        /*
        ret = relay_turn_on(&Relay_1);
        __delay_ms(5000);
        ret = relay_turn_off(&Relay_1);
        __delay_ms(5000);
        */
        
        /************* DC Motor Example *************/
        /*
        dc_motor_move_right(&DC_Motor_1);
        dc_motor_move_left(&DC_Motor_2);
        __delay_ms(5000);
        dc_motor_stop(&DC_Motor_1);
        dc_motor_stop(&DC_Motor_2);
        __delay_ms(5000);
        dc_motor_move_left(&DC_Motor_1);
        dc_motor_move_right(&DC_Motor_2);
        __delay_ms(5000);
        */
        
        /************* Seven Segment Example *************/
        
       // ret = seven_segment_write_number(&seg_1, 9);
    }
    
    return 0;
}

/* Section: Function Definitions */

void application_initialize(void)
{   
    //ret = gpio_pin_initialize(&Pin_1);
    //ret = gpio_pin_initialize(&btn_1);
    //ret = gpio_port_direction_initialize(PORTC_INDEX, 0x00);
    
    /************* LED Example *************/
    
    ret = led_initialize(&LED_1);
    
    /************* Button Example *************/
    
    //ret = button_initialize(&BTN_1);
    //ret = button_initialize(&BTN_2);
    
    /************* Relay Example *************/
    
    //ret = relay_initialize(&Relay_1);
    
    /************* DC Motor Example *************/
    
    //ret = dc_motor_initialize(&DC_Motor_1);
    //ret = dc_motor_initialize(&DC_Motor_2);
    
    /************* Seven Segment Example *************/
    
    //ret = seven_segment_initialize(&seg_1);
    
    ret = interrupt_INTx_Init(&INT0_obj);
    
    
}

void INT0_ISR_APP(void)
{
    led_toggle(&LED_1);
}