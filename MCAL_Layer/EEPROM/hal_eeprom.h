/* 
 * File:   hal_eeprom.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/06, 10:34
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/************************** Section: Includes **************************/

#include "xc.h"
#include "../mcal_std_types.h"
#include "../Interrupt/mcal_internal_interrupt.h"

/************************** Section: Macro Declarations **************************/

#define ACCESS_FLASH_MEMORY                     0x01U
#define ACCESS_EEPROM_MEMORY                    0x00U

#define ACCESS_CONFIG_REGISTERS                 0x01U
#define ACCESS_FLASH_EEPROM_MEMORY              0x00U

#define ALLOW_WRITE_CYCLES_MEMORY               0x01U
#define INHIBIT_WRITE_CYCLES_MEMORY             0x00U

#define INITIATE_EEPROM_WRITE_CYCLE             0x01U
#define EEPROM_WRITE_CYCLE_COMPLETE             0x00U

#define INITIATE_EEPROM_READ_CYCLE              0x01U
#define EEPROM_READ_CYCLE_COMPLETE              0x00U


/************************** Section: Macro Function Declarations **************************/

/************************** Section: Data Type Declarations **************************/

/************************** Section: Function Declarations **************************/

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

