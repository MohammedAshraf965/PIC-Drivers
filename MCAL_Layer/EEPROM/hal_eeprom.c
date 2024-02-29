/* 
 * File:   hal_eeprom.c
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/06, 10:34
 */

/************************** Section: Includes **************************/

#include "hal_eeprom.h"

/************************** Section: Macro Declarations **************************/

/************************** Section: Macro Function Declarations **************************/

/************************** Section: Data Type Declarations **************************/

/************************** Section: Function Declarations **************************/

/**
 * @brief Write data to the address bAdd
 * @param bAdd Address of the destination
 * @param bData Data to be send to the address bAdd
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData)
{
    Std_ReturnType ret = E_NOK;
    
    /* Read the Interrupt Status: Enabled or Disabled*/
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    
    /* Update the Address Registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x33);
    EEADR = (uint8)(bAdd & 0xFF);
    
    /* Update the Data Registers */
    EEDATA = bData;
    
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    EECON1bits.CFGS =  ACCESS_FLASH_EEPROM_MEMORY;
    
    /* Allow write cycles to Flash program/data EEPROM*/
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_MEMORY;

    /* Disable all interrupts */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_InterruptPriorityDisable();
#else
    INTERRUPT_GlobalInterruptDisable();
#endif
    /* Write the required sequence: 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    /* Initiate data EEPROM erase/write cycles */
    EECON1bits.WR = INITIATE_EEPROM_WRITE_CYCLE;
    
    /* Wait for write to complete */
    while(EECON1bits.WR != EEPROM_WRITE_CYCLE_COMPLETE);
    
    /* Inhibit write cycles to Flash program/data EEPROM */
    EECON1bits.WREN = INHIBIT_WRITE_CYCLES_MEMORY;
    
    /* Restore the Interrupt Status */
    INTCONbits.GIE = Global_Interrupt_Status;
    
    return ret;
}

/**
 * @brief Read data from the address bAdd
 * @param bAdd Address of the destination
 * @param bData Address to store the data from the address bAdd
 * @return Status of the function
 *              E_OK: Function returned successfully
 *              E_NOK: Function failed to return
 */
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData)
{
    Std_ReturnType ret = E_NOK;
    
    if(bData == NULL)
    {
        ret = E_NOK;
    }
    else
    {
        /* Update the Address Registers*/
        EEADRH = (uint8)((bAdd >> 8) & 0x33);
        EEADR = (uint8)(bAdd & 0xFF);
        
        /* Select Access data EEPROM Memory*/
        EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
        EECON1bits.CFGS =  ACCESS_FLASH_EEPROM_MEMORY;
        
        /* Initiate EEPROM Data Read Cycle*/
        EECON1bits.RD = INITIATE_EEPROM_READ_CYCLE;
        NOP();
        NOP();
        
        /* Read data */
        *bData = EEDATA;
        
        ret = E_OK;
    }
    
    return ret;    
}