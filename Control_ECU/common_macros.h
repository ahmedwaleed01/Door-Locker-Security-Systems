/*
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 * Author: ahmed waleed
 *
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT)       (REG |= (1<<BIT))
/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT)     (REG &= ~(1<<BIT))
/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT)    (REG ^= (1<<BIT))
/* Rotate right the register value with specific number of rotates */
#define ROR(REG,NUM)           ( REG=(REG>>NUM) | (REG<<( 8*(sizeof(REG))-NUM) ))
/* Rotate left the register value with specific number of rotates */
#define ROL(REG,NUM)           ( REG=(REG<<NUM) | (REG>>( 8*(sizeof(REG))-NUM) ))
/* Check if a specific bit is set in any register and return true if yes */
#define IS_SET(REG,BIT)        (REG & (1<<BIT))
/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT)      (!(REG & (1<<BIT)))
/* Get a bit in any register */
#define GET_BIT(REG,BIT) ( ( REG & (1<<BIT) ) >> BIT )

#endif /* COMMON_MACROS_H_ */
