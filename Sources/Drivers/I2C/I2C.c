/*
 * I2C.c
 *
 *  Created on: May 16, 2019
 *      Author: PCO
 */

#include "I2C.h"



/* initialize I2C1 and the port pins */
void I2C1_init(void) {
	SIM_SCGC4 |= 0x80; /* turn on clock to I2C1 */
	SIM_SCGC5 |= 0x2000; /* turn on clock to PortE */
	PORTE_PCR1 = 0x0600; /* PTE1 I2C1 SCL */
	PORTE_PCR0 = 0x0600; /* PTE0 I2C1 SDA */
	I2C1_C1 = 0; /* stop I2C1 */
	I2C1_S = 2; /* Clear interrupt flag */
	I2C1_F = 0x1C; /* set clock to 97.09KHz @13.981MHz bus clock */
	/* See Table 9-4. */
	I2C1_C1 = 0x80; /* enable I2C1 */
}

/* Write a single byte to slave memory.
* write: S-(saddr+w)-ACK-maddr-ACK-data-ACK-P
*/
int I2C1_byteWrite(unsigned char slaveAddr, unsigned char memAddr, unsigned char data) {
	int retry = 1000;
	while (I2C1_S & 0x20) { /* wait until bus is available */
		if (--retry <= 0)
			return ERR_BUS_BUSY;
		delayUs(100);
	}
	/* send start */
	I2C1_C1 |= 0x10; /* Tx on */
	I2C1_C1 |= 0x20; /* become master */
	/* send slave address and write flag */
	I2C1_D = slaveAddr << 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x10) { /* arbitration lost */
		I2C1_S |= 0x10; /* clear IF */
		return ERR_ARB_LOST;
	}
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send memory address */
	I2C1_D = memAddr;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send data */
	I2C1_D = data;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* stop */
	I2C1_C1 &= ~0x30;
	return ERR_NONE;
}

/* Use burst write to write multiple bytes to consecutive memory locations.
* Burst write: S-(saddr+w)-ACK-maddr-ACK-data-ACK-data-ACK-…-data-ACK-P
*/
int I2C1_burstWrite(unsigned char slaveAddr, unsigned char memAddr, int byteCount, unsigned char* data, int* cnt) 
{
	int retry = 1000;
	*cnt = 0;
	while (I2C1_S & 0x20) { /* wait until bus is available */
		if (--retry <= 0)
			return ERR_BUS_BUSY;
		delayUs(100);
	}
	/* send start */
	I2C1_C1 |= 0x10; /* Tx on */
	I2C1_C1 |= 0x20; /* become master */
	/* send slave address and write flag */
	I2C1_D = slaveAddr << 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x10) { /* arbitration lost */
		I2C1_S |= 0x10; /* clear IF */
		return ERR_ARB_LOST;
	}
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send memory address */
	I2C1_D = memAddr;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send data */
	while (byteCount-- > 0) {
		I2C1_D = *data++;
		while(!(I2C1_S & 0x02)); /* wait for transfer complete */
		I2C1_S |= 0x02; /* clear IF */
		if (I2C1_S & 0x01) /* got NACK from slave */
			return ERR_NO_ACK;
		(*cnt)++;
	}
	/* stop */
	I2C1_C1 &= ~0x30;
	return ERR_NONE;
}

int I2C1_byteRead(unsigned char slaveAddr, unsigned char memAddr, unsigned char* data) {
	int retry = 100;
	volatile unsigned char dummy;
	while (I2C1_S & 0x20) { /* wait until bus is available */
		if (--retry <= 0)
			return ERR_BUS_BUSY;
			delayUs(100);
	}
	/* start */
	I2C1_C1 |= 0x10; /* Tx on */
	I2C1_C1 |= 0x20; /* become master */
	/* send slave address and write flag */
	I2C1_D = slaveAddr << 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x10) /* arbitration lost */
		return ERR_ARB_LOST;
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send address of target register in slave */
	I2C1_D = memAddr;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* restart */
	I2C1_C1 |= 0x04; /* send Restart */
	/* send slave address and read flag */
	I2C1_D = (slaveAddr << 1) | 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* change bus direction to read */
	I2C1_C1 &= ~0x18; /* Tx off, prepare to give ACK */
	I2C1_C1 |= 0x08; /* prepare to give NACK */
	dummy = I2C1_D; /* dummy read to initiate bus read */
	/* read data */
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	I2C1_C1 &= ~0x20; /* stop the bus before reading last byte */
	
	*data = I2C1_D; /* read received data */
	
	return ERR_NONE;
}

/* Use burst read to read multiple bytes from consecutive memory locations.
Burst read: S-(saddr+w)-ACK-maddr-ACK-R-(saddr+r)-data-ACK-data-ACK-…-data-
NACK-P
*/
int I2C1_burstRead(unsigned char slaveAddr, unsigned char memAddr, int byteCount, unsigned char* data, int* cnt) 
{
	int retry = 100;
	volatile unsigned char dummy;
	*cnt = 0;
	while (I2C1_S & 0x20) { /* wait until bus is available */
		if (--retry <= 0)
			return ERR_BUS_BUSY;
			delayUs(100);
	}
	/* start */
	I2C1_C1 |= 0x10; /* Tx on */
	I2C1_C1 |= 0x20; /* become master */
	/* send slave address and write flag */
	I2C1_D = slaveAddr << 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x10) /* arbitration lost */
		return ERR_ARB_LOST;
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* send address of target register in slave */
	I2C1_D = memAddr;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* restart */
	I2C1_C1 |= 0x04; /* send Restart */
	/* send slave address and read flag */
	I2C1_D = (slaveAddr << 1) | 1;
	while(!(I2C1_S & 0x02)); /* wait for transfer complete */
	I2C1_S |= 0x02; /* clear IF */
	if (I2C1_S & 0x01) /* got NACK from slave */
		return ERR_NO_ACK;
	/* change bus direction to read */
	I2C1_C1 &= ~0x18; /* Tx off, prepare to give ACK */
	if (byteCount == 1)
		I2C1_C1 |= 0x08; /* prepare to give NACK */
	dummy = I2C1_D; /* dummy read to initiate bus read */
	/* read data */
	while (byteCount > 0) {
		if (byteCount == 1)
			I2C1_C1 |= 0x08; /* prepare to give NACK for last byte */
		while(!(I2C1_S & 0x02)); /* wait for transfer complete */
		I2C1_S |= 0x02; /* clear IF */
		if (byteCount == 1) {
			I2C1_C1 &= ~0x20; /* stop the bus before reading last byte */
		}
		*data++ = I2C1_D; /* read received data */
		byteCount--;
		(*cnt)++;
	}
	return ERR_NONE;
}
