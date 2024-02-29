/* 
 * File:   mcal_std_types.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/11/26, 9:12
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section: Includes */

#include "std_libraries.h"
#include "compiler.h"
#include "Platform_Types.h"

/* Section: Macro Declarations */

#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define E_OK            (Std_ReturnType)0x01
#define E_NOK           (Std_ReturnType)0x01

#define ZERO_INIT       0x00

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

typedef uint8 Std_ReturnType;

/* Section: Function Declarations */

#endif	/* MCAL_STD_TYPES_H */

