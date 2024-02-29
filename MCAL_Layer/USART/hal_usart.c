/* 
 * File:   hal_usart.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/14, 13:29
 */

/************************** Section: Includes **************************/

#include <pic18f4620.h>

#include "hal_usart.h"

/************************** Section: Function Declarations **************************/

static Std_ReturnType EUSART_BAUD_RATE_CALCULATION(const usart_t *_eusart);

/************************** Section: Data Type Declarations **************************/

/************************** Section: Function Definitions **************************/

/**
 * 
 * @param _eusart
 * @return 
 */
Std_ReturnType EUSART_Init(const usart_t *_eusart)
{
    Std_ReturnType ret = E_NOK;
    
    if(_eusart == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        ret = EUSART_BAUD_RATE_CALCULATION(_eusart);
    }
    
    return ret;
}

/**
 * 
 * @param _eusart
 * @return 
 */
Std_ReturnType EUSART_DeInit(const usart_t *_eusart)
{
    Std_ReturnType ret = E_NOK;
    
    if(_eusart == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        
    }
    
    return ret;
}

/**
 * 
 * @param _eusart
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_eusart, uint8 *_data)
{
    Std_ReturnType ret = E_NOK;
    
    if((_eusart == NULL) || (_data == NULL))
    {
        ret = E_NOK;
    }
    else
    {
        
    }
    
    return ret;
}

/**
 * 
 * @param _eusart
 * @param _data
 * @return 
 */
Std_ReturnType EUSART_WriteByteBlocking(const usart_t *_eusart, uint8 _data)
{
    Std_ReturnType ret = E_NOK;
    
    if(_eusart == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        
    }
    
    return ret;
}



/*********************/

static Std_ReturnType EUSART_BAUD_RATE_CALCULATION(const usart_t *_eusart)
{
    Std_ReturnType ret = E_NOK;
    
    if(_eusart == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        float Baud_Rate_Temp= 0;
        
        switch(_eusart -> baudrate_gen_config)
        {
            case BAUDRATE_ASYN_8BIT_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 64) - 1;
                break;
            case BAUDRATE_ASYN_16BIT_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 16) - 1;
                break;
            case BAUDRATE_ASYN_8BIT_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 16) - 1;
                break;
            case BAUDRATE_ASYN_16BIT_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 4) - 1;
                break;
            case BAUDRATE_SYN_8BIT:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_08BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 4) - 1;
                break;
            case BAUDRATE_SYN_16BIT:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                Baud_Rate_Temp = ((_XTAL_FREQ / (float)_eusart -> baudrate) / 4) - 1;
                break;
            default:
                break;
        }
        
        SPBRG = (uint8)((uint32)Baud_Rate_Temp);
        SPBRGH = (uint8)(x((uint32)Baud_Rate_Temp) >> 8);
    }
    
    return ret;
}