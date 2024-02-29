/* 
 * File:   hal_usart.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/14, 13:29
 */

#ifndef HAL_USART_H
#define	HAL_USART_H

/************************** Section: Includes **************************/

#include <xc.h>
#include "hal_usart_config.h"
#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
//#include "../Interrupt/mcal_internal_interrupt.h"


/************************** Section: Macro Declarations **************************/

/* Selecting EUSART Workout mode */
#define EUSART_SYNCHRONOUS_MODE                     1
#define EUSART_ASYNCHRONOUS_MODE                    0
/* Baud Rate Generator Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED              1
#define EUSART_ASYNCHRONOUS_LOW_SPEED               0
/* Baud Rate Generator Register Size */
#define EUSART_16BIT_BAUDRATE_GEN                   1
#define EUSART_08BIT_BAUDRATE_GEN                   0

/* EUASRT Transmit Enable */
#define EUSART_ASYNCHRONOUS_TX_ENABLE               1
#define EUSART_ASYNCHRONOUS_TX_DISABLE              0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_TX_DISABLE    0
/* EUSART 9-bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_TX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_TX_DISABLE         0

/* EUASRT Receive Enable */
#define EUSART_ASYNCHRONOUS_RX_ENABLE               1
#define EUSART_ASYNCHRONOUS_RX_DISABLE              0
/* EUSART Transmit Interrupt Enable */
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_ENABLE     1
#define EUSART_ASYNCHRONOUS_INTERRUPT_RX_DISABLE    0
/* EUSART 9-bit Transmit Enable */
#define EUSART_ASYNCHRONOUS_9BIT_RX_ENABLE          1
#define EUSART_ASYNCHRONOUS_9BIT_RX_DISABLE         0

/* EUSART Framing Error */
#define EUSART_FRAMING_ERROR_DETECTED               1
#define EUSART_FRAMING_ERROR_CLEARED                0
/* EUSART Overrun Error */
#define EUSART_OVERRUN_ERROR_DETECTED               1
#define EUSART_OVERRUN_ERROR_CLEARED                0

/************************** Section: Macro Function Declarations **************************/

/************************** Section: Data Type Declarations **************************/

typedef enum
{
    BAUDRATE_ASYN_8BIT_LOW_SPEED,
    BAUDRATE_ASYN_16BIT_LOW_SPEED,
    BAUDRATE_ASYN_8BIT_HIGH_SPEED,
    BAUDRATE_ASYN_16BIT_HIGH_SPEED,
    BAUDRATE_SYN_8BIT,
    BAUDRATE_SYN_16BIT        
}baudrate_gen_t;

typedef struct
{
    uint8 usart_tx_reserved         :5;
    uint8 usart_tx_enable           :1;
    uint8 usart_tx_interrupt_enable :1;
    uint8 usart_tx_9bit_enable      :1;
}usart_tx_cfg_t;

typedef struct
{
    uint8 usart_rx_reserved         :5;
    uint8 usart_rx_enable           :1;
    uint8 usart_rx_interrupt_enable :1;
    uint8 usart_rx_9bit_enable      :1;
}usart_rx_cfg_t;

typedef union
{
    struct
    {
        uint8 usart_errot_reserved  :6;
        uint8 usart_ferr            :1;
        uint8 usart_oerr            :1;
    };
    uint8 status;
}usart_error_status_t;

typedef struct
{
    uint32 baudrate;
    baudrate_gen_t baudrate_gen_config;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_error_status_t error_status;
    void (*EUSART_TxDefaultInterruptHandler)(void);
    void (*EUSART_RxDefaultInterruptHandler)(void);
    void (*EUSART_FramingErrorHandler)(void);
    void (*EUSART_OverrunErrorHandler)(void);
}usart_t; 

/************************** Section: Function Declarations **************************/

Std_ReturnType EUSART_Init(const usart_t *_eusart);
Std_ReturnType EUSART_DeInit(const usart_t *_eusart);
Std_ReturnType EUSART_ReadByteBlocking(const usart_t *_eusart, uint8 *_data);
Std_ReturnType EUSART_WriteByteBlocking(const usart_t *_eusart, uint8 _data);

#endif	/* HAL_USART_H */

