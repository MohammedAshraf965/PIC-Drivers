/* 
 * File:   mcal_interrupt_gen_config.h
 * Author: Mohammed Ashraf
 *
 * Created on 2023/12/02, 10:50
 */

#ifndef MCAL_INTERRUPT_GEN_CONFIG_H
#define	MCAL_INTERRUPT_GEN_CONFIG_H

/* Section: Includes */

/* Section: Macro Declarations */

#define INTERRUPT_FEATURE_ENABLE                    0x01U
#define INTERRUPT_FEATURE_DISABLE                   0x00U
#define INTERRUPT_PRIORITY_LEVELS_ENABLE            INTERRUPT_FEATURE_DISABLE
#define EXTERNAL_INTERRUPT_INTx_ENABLE              INTERRUPT_FEATURE_ENABLE
#define EXTERNAL_INTERRUPT_OnChange_ENABLE          INTERRUPT_FEATURE_ENABLE
#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE
#define TIMER0_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

/* Section: Macro Function Declarations */

/* Section: Data Type Declarations */

/* Section: Function Declarations */

#endif	/* MCAL_INTERRUPT_GEN_CONFIG_H */

