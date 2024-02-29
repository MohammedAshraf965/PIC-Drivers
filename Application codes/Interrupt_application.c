/* 
 * File:   application.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:18
 */


/************************** Section: Includes **************************/

#include "application.h"

/* Section: Function Declarations */
void RB4_ISR_APP(void);
void RB5_ISR_APP(void);
void RB6_ISR_APP(void);
void RB7_ISR_APP(void);
/************************** Varaible Definitions **************************/
led_t LED_1 =
{
    .portname = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

led_t LED_2 =
{
    .portname = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};

led_t LED_3 =
{
    .portname = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};

led_t LED_4 =
{
    .portname = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = GPIO_LOW
};


interrupt_RBx_t RB4_obj =
{
    .EXT_InterruptHandler = RB4_ISR_APP,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB5_obj =
{
    .EXT_InterruptHandler = RB5_ISR_APP,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB6_obj =
{
    .EXT_InterruptHandler = RB6_ISR_APP,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB7_obj =
{
    .EXT_InterruptHandler = RB7_ISR_APP,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN7,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

Std_ReturnType ret = E_NOK;

/************************** Section: Function Definitions **************************/

int main()
{   
    application_initialize();

    while(1)
    {  
       
    }
    
    return 0;
}

void application_initialize(void)
{   
    
    ret = led_initialize(&LED_1);
    ret = led_initialize(&LED_2);
    ret = led_initialize(&LED_3);
    ret = led_initialize(&LED_4);
    
    ret = interrupt_RBx_Init(&RB4_obj);
    //ret = interrupt_RBx_Init(&RB5_obj);
    //ret = interrupt_RBx_Init(&RB6_obj);
    //ret = interrupt_RBx_Init(&RB7_obj);   
}

void RB4_ISR_APP(void)
{
    led_toggle(&LED_1);
}

void RB5_ISR_APP(void)
{
    led_toggle(&LED_2);
}

void RB6_ISR_APP(void)
{
    led_toggle(&LED_3);
}

void RB7_ISR_APP(void)
{
    led_toggle(&LED_4);
}
