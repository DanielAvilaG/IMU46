/*
 * LSM9DS1.c
 *
 *  Created on: May 17, 2019
 *      Author: Dani
 */

#include "LSM9DS1.h"

void LSM9DS1_mag_read() 
{
	int rv = 1, count = 6;
	int16_t data[3];

	rv = I2C1_byteWrite(0x1E, 0x22, 0x01); // Set single mode
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_burstRead(0x1E, 0x28, 6, (unsigned char*)data, &count);
	if (rv) for(;;) ; // replace with error handling 

	Raw_Data.mx = data[0];
	Raw_Data.my = data[1];
	Raw_Data.mz = data[2];
}
