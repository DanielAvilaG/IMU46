/*
 * GY85.h
 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */

#ifndef GY85_H_
#define GY85_H_

#include "../I2C/I2C.h"

typedef struct Raw {
	// These values are the RAW signed 16-bit readings from the sensors.
	int16_t mx, my, mz; // x, y, and z axis readings of the magnetometer
	int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
	int16_t ax, ay, az; // x, y, and z axis readings of the accelerometer
	
} volatile Raw;

Raw Raw_Data;

void GY85_mag_init(void);
void GY85_acc_init(void);

void GY85_acc_read(void);
void GY85_mag_read(void);

#endif /* GY85_H_ */
