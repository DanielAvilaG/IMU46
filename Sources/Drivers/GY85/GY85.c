/*
 * GY85.c

 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */

#include "GY85.h"

void GY85_mag_read() {
	int rv = 1, count = 6, ready = 0;
	char buffer[50];
	char data;
	char data1[6];
	char data2[6];
	int16_t *xyz;

	rv = I2C1_byteWrite(0x1E, 0x00, 0x70); // clear bit 7
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x01, 0xA0); // Set Gain 4.7
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x02, 0x01); // Set single mode
	if (rv) for(;;) ; // replace with error handling 
	while (!ready) {
		delayUs(250);
		rv = I2C1_byteRead(0x1E, 0x09, &data);
		if (rv) for(;;) ; // replace with error handling 
		ready = (data & 0x01);
	}
	rv = I2C1_burstRead(0x1E, 0x03, 6, data1, &count);
	if (rv) for(;;) ; // replace with error handling 
	
	data2[0]=data1[1];
	data2[1]=data1[0];
	data2[2]=data1[3];
	data2[3]=data1[2];
	data2[4]=data1[5];
	data2[5]=data1[4];
	xyz = data2;
	
	Raw_Data.mx = xyz[0];
	Raw_Data.my = xyz[1];
	Raw_Data.mz = xyz[2];
	
	sprintf(buffer,"HMC rv: %d -- mx: %d -- my: %d -- mz: %d", rv, Raw_Data.mx, Raw_Data.my, Raw_Data.mz);
	UART0_send_string_ln(buffer);
}

void GY85_acc_read() {
	int rv = 1, count = 6, ready = 0;
	char buffer[50];
	char data;
	char data1[7];
	char data2[7];
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
	
	data2[0]=data1[1];
	data2[1]=data1[0];
	data2[2]=data1[3];
	data2[3]=data1[2];
	data2[4]=data1[5];
	data2[5]=data1[4];
	xyz = data1;
	
	Raw_Data.ax = xyz[0];
	Raw_Data.ay = xyz[1];
	Raw_Data.az = xyz[2];
	
	sprintf(buffer,"ADXL rv: %d -- ax: %d -- ay: %d -- az: %d", rv, Raw_Data.ax, Raw_Data.ay, Raw_Data.az);
	//sprintf(buffer,"ADXL rv: %d -- ax: %d -- ay: %d -- az: %d", rv, xyz[0], xyz[1], xyz[2]);
	UART0_send_string_ln(buffer);
	//sprintf(buffer,"ADXL: -- pitch: %2.1f -- roll: %2.1f ", pitch, roll);
	//UART0_send_string_ln(buffer);
}

void GY85_acc_init()
{
	// INIT ACCEL
	int rv;
	rv = I2C1_byteWrite(0x53, 0x31, 0x80); // Self Test ON
	if (rv) for(;;) ; // replace with error handling */
	delayMs(100);
	
	//ADXL();
	
	rv = I2C1_byteWrite(0x53, 0x31, 0x00); // Self Test OFF
	if (rv) for(;;) ; // replace with error handling */
	
	rv = I2C1_byteWrite(0x53, 0x2E, 0x80); // Set DATA_READY int_enable
	if (rv) for(;;) ; // replace with error handling
	rv = I2C1_byteWrite(0x53, 0x31, 0x00); // Set RANGE to +-2g
	if (rv) for(;;) ; // replace with error handling */
	rv = I2C1_byteWrite(0x53, 0x2D, 0x08); // Set measure bit on POWER_CTL register
	if (rv) for(;;) ; // replace with error handling 
}

void GY85_mag_init()
{
	// INIT HMC 
	int rv;
	rv = I2C1_byteWrite(0x1E, 0x00, 0x70); // clear bit 7
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x01, 0xA0); // Set Gain 4.7
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x02, 0x01); // Set single mode
	if (rv) for(;;) ; // replace with error handling 
	
	// Calibrate
	/**
	 * If the configuration register B is left at the factory default value of 0x40, 
	 * values around +951 ADC LSB (1.16 Ga * 820 LSB/Ga) will be placed in the X and Y data output registers and around +886 (1.08 Ga * 1820 LSB/Ga) 
	 * in Z data output register. To leave the self test mode, change MS1 and MS0 bit of the configuration register A back to 00. 
	 * Also change the mode register if single-measurement mode is not the intended mode of operation.
	 */
	
	/*
	rv = I2C1_byteWrite(0x1E, 0x00, 0x01); // Set MS0 bit of A configuration Register to calibrating
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x01, 0x40); // Set configuration register B
		if (rv) for(;;) ; // replace with error handling 
	HMC();
	HMC();
	rv = I2C1_byteWrite(0x1E, 0x00, 0x00); // Set MS0 bit of A configuration Register to normal measurement
	if (rv) for(;;) ; // replace with error handling 
	rv = I2C1_byteWrite(0x1E, 0x01, 0x20); // Set MS0 bit of B configuration Register to normal measurement
	if (rv) for(;;) ; // replace with error handling */
}

int GY85_test()
{
	char buffer[20];
	UART0_send_string_ln("Start GY_85 test:");
	unsigned char data, data1[13];
	int count;
	int rv;
	//I2C1_init();
	//rv = I2C1_burstRead(0x68, 0, 1, data1, &count);
	rv = I2C1_byteRead(0x68, 0x00, &data);
	if (rv)
		for(;;); /* replace with error handling */
	sprintf(buffer,"0x68 rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	rv = I2C1_byteRead(0x53, 0x00, &data);
	if (rv)
		for(;;) ; /* replace with error handling */
	sprintf(buffer,"0x53 rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	rv = I2C1_byteRead(0x1E, 0x0C, &data);
	if (rv)
			for(;;) ; /* replace with error handling */
	sprintf(buffer,"0x1E rv: %d -- data: %d", rv, data);
	UART0_send_string_ln(buffer);
	//UART0_send_string_ln(data);
	return 0;
}

