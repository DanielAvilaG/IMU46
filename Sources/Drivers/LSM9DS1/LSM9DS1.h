/*
 * LSM9DS1.h
 *
 *  Created on: May 17, 2019
 *      Author: Dani
 */

#ifndef LSM9DS1_H_
#define LSM9DS1_H_

#include <stdio.h>
#include "../../MKL46Z4.h"

/** BP - Peripheral register structure */
typedef struct Raw {
	// These values are the RAW signed 16-bit readings from the sensors.
	int16_t mx, my, mz; // x, y, and z axis readings of the magnetometer
	int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
	int16_t ax, ay, az; // x, y, and z axis readings of the accelerometer
	
} volatile Raw;

Raw Raw_Data;

void LSM9DS1_mag_read();





#endif /* LSM9DS1_H_ */
