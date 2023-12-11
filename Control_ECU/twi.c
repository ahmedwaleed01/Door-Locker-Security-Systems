/*
 * twi.c
 *
 *  Created on: 24 Oct 2023
 *      Author: ahmed waleed
 */


#include "twi.h"
#include <avr/io.h>
#include "common_macros.h"


void TWI_init(TWI_ConfigType*config_ptr){
	/* Set Bit Rate Value */
	TWBR=config_ptr->bit_rate;
	/* Prescalar value = 0 (TWPS) */
	TWSR = 0x00;
	TWAR =config_ptr->address;

	/* Enable I2C */
	TWCR=(1<<TWEN);


}

void TWI_start(void){

	TWCR=(1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void){
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);

}

void TWI_writeByte(uint8 data){
	TWDR=data;

	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
uint8 TWI_readByteWithACK(void){
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_readByteWithNACK(void){

	TWCR = (1 << TWINT) | (1 << TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}
uint8 TWI_getStatus(void)
{
	uint8 status;
	status=TWSR&(0xf8);
	return status;
}
