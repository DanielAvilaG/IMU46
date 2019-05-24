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

void LSM9DS1_acc_read() {
	int rv = 1, count = 6, ready = 0;
	char buffer[50];
	unsigned char data;
	unsigned char data1[7];
	//unsigned char data2[7];
	int16_t *xyz;
	while (!ready) {
		//delayUs(1000);
		rv = I2C1_byteRead(0x53, 0x30, &data);
		if (rv) for(;;) ; // replace with error handling 
		ready = (data & 0x01 && data & 0x02 && data & 0x80); // data == 1000 0011
		//sprintf(buffer,"0x30 rv: %d -- data: %d", rv, data);
		//UART0_send_string_ln(buffer);
	}
	/*
	rv = I2C1_byteRead(0x53, 0x38, &data);
	if (rv)
		for(;;) ; // replace with error handling 
	sprintf(buffer,"0x38 rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	*/
		
	rv = I2C1_burstRead(0x53, 0x32, 6, data1, &count);
	if (rv) for(;;) ; // replace with error handling 
	
	/*data2[0]=data1[1];
	data2[1]=data1[0];
	data2[2]=data1[3];
	data2[3]=data1[2];
	data2[4]=data1[5];
	data2[5]=data1[4];*/
	xyz = (int16_t *)data1;
	
	Raw_Data.ax = xyz[0];
	Raw_Data.ay = xyz[1];
	Raw_Data.az = xyz[2];
	
	sprintf(buffer,"ADXL rv: %d -- ax: %d -- ay: %d -- az: %d", rv, Raw_Data.ax, Raw_Data.ay, Raw_Data.az);
	//sprintf(buffer,"ADXL rv: %d -- ax: %d -- ay: %d -- az: %d", rv, xyz[0], xyz[1], xyz[2]);
	UART0_send_string_ln(buffer);
	//sprintf(buffer,"ADXL: -- pitch: %2.1f -- roll: %2.1f ", pitch, roll);
	//UART0_send_string_ln(buffer);
}
