/*
 * I2C.h
 *
 *  Created on: May 16, 2019
 *      Author: PCO
 */

#ifndef I2C_H_
#define I2C_H_

#include "../../MKL46Z4.h"

#define SLAVE_ADDR 0x68
#define ERR_NONE 0
#define ERR_NO_ACK 0x01
#define ERR_ARB_LOST 0x02
#define ERR_BUS_BUSY 0x03

void I2C1_init(void);
int I2C1_byteWrite(unsigned char , unsigned char , unsigned char );
int I2C1_burstWrite(unsigned char , unsigned char , int , unsigned char* , int* ) ;
int I2C1_byteRead(unsigned char , unsigned char , unsigned char* );
int I2C1_burstRead(unsigned char , unsigned char , int , unsigned char* , int* );

#endif /* I2C_H_ */
