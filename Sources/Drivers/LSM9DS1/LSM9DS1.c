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

	rv = I2C1_byteWrite(ADDR_M, CTRL_REG3_M, 0x01); // Set single mode
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_burstRead(ADDR_M, OUT_X_L_M, 6, (unsigned char*)data, &count);
	if (rv) for(;;) ; // replace with error handling 

	Raw_Data.mx = data[0];
	Raw_Data.my = data[1];
	Raw_Data.mz = data[2];
	
#ifdef DEBUG
	char buffer[50];
	sprintf(buffer,"ADDR_M rv: %d -- mx: %d -- my: %d -- mz: %d", rv, Raw_Data.mx, Raw_Data.my, Raw_Data.mz);
	UART0_send_string_ln(buffer);
#endif
}

void LSM9DS1_acc_read() {
	int rv = 1, count = 6;
	unsigned char data[6];
	int16_t *xyz;
	
	rv = I2C1_byteWrite(ADDR_XG, CTRL_REG6_XL, 0x50); // Set ODR 50 Hz, 4g full scale
	if (rv) for(;;) ; // replace with error handling 
	
	rv = I2C1_burstRead(ADDR_XG, OUT_X_L_XL, 6, data, &count);
	if (rv) for(;;) ; // replace with error handling 

	xyz = (int16_t *)data;
	
	Raw_Data.ax = xyz[0];
	Raw_Data.ay = xyz[1];
	Raw_Data.az = xyz[2];
	
#ifdef DEBUG
	char buffer[50];
	sprintf(buffer,"ADDR_XG rv: %d -- ax: %d -- ay: %d -- az: %d", rv, Raw_Data.ax, Raw_Data.ay, Raw_Data.az);
	UART0_send_string_ln(buffer);
#endif
}

int LSM9DS1_test()
{
	char buffer[20];
	UART0_send_string_ln("Start LSM9DS1 test:");
	unsigned char data;

	int rv;
	rv = I2C1_byteRead(ADDR_M, WHO_AM_I_M, &data);
	if (rv)
	for(;;); /* replace with error handling */
	sprintf(buffer,"ADDR_M rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	
	rv = I2C1_byteRead(ADDR_XG, WHO_AM_I_XG, &data);
	if (rv)
	for(;;) ; /* replace with error handling */
	sprintf(buffer,"ADDR_XG rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	
	return 0;
}
