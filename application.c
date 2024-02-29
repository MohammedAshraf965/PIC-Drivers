/* 
 * File:   application.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:18
 */


/************************** Section: Includes **************************/

#include "application.h"

/************************** Section: Function Declarations **************************/

void ADC_DefaultInterrupt(void);

/************************** Variable Definitions **************************/

Std_ReturnType ret = E_NOK;

uint8 value = 0;

/************************** Section: Function Definitions **************************/

int main()
{   
    application_initialize();
    
  
    //ret = lcd_4bit_send_char_data(&lcd_4bit, 'A'); /* Does not Work */
    //ret = lcd_4bit_send_char_data_pos(&lcd_4bit, 2, 2, 'A'); /* Does not Work */
    //ret = lcd_4bit_send_string(&lcd_4bit, "Mohammed"); /* Does not Work */
    //ret = lcd_4bit_send_string_pos(&lcd_4bit, 3, 3, "Mohammed");
  
    
    //ret = lcd_8bit_send_char_data(&lcd_8bit, 'A'); /* Works */
    //ret = lcd_8bit_send_char_data_pos(&lcd_8bit, 2, 2, 'A'); /* Works */
    //ret = lcd_8bit_send_string(&lcd_8bit, "Mohammed"); /* Works */
    //ret = lcd_8bit_send_string_pos(&lcd_8bit, 3, 3, "Mohammed"); /* Works */
    
    while(1)
    {
        /*
        ret = lcd_8bit_send_string_pos(&lcd_8bit, 1, 1, "Mohammed");
        ret = lcd_8bit_send_string_pos(&lcd_8bit, 2, 2, "Mohammed");
        ret = lcd_8bit_send_string_pos(&lcd_8bit, 3, 3, "Mohammed");
        ret = lcd_8bit_send_string_pos(&lcd_8bit, 4, 4, "Mohammed");
        
        
        ret = lcd_4bit_send_string_pos(&lcd_4bit, 1, 1, "Mohammed");
        ret = lcd_4bit_send_string_pos(&lcd_4bit, 2, 2, "Mohammed");
        ret = lcd_4bit_send_string_pos(&lcd_4bit, 3, 3, "Mohammed");
        ret = lcd_4bit_send_string_pos(&lcd_4bit, 4, 4, "Mohammed");
        */
    }
    
    return 0;
}

void application_initialize(void)
{   
    ecu_layer_init();
}

void ADC_DefaultInterrupt(void)
{
    
}