/*
 * common.h
 *
 *  Created on: May 22, 2019
 *      Author: Dani
 */

#ifndef COMMON_H_
#define COMMON_H_

//#define GY85
#define LSM9DS1

#include <stdio.h>
#include <math.h>
#include "MKL46Z4.h"
#include "FRTOS1.h"
#include "LED1.h"
#include "LED2.h"
#include "Drivers/UART/UART.h"
#include "Drivers/I2C/I2C.h"

#ifdef GY85
	#include "Drivers/GY85/GY85.h"
#endif
#ifdef LSM9DS1
	#include "Drivers/LSM9DS1/LSM9DS1.h"
#endif

// http://bit.do/KL46z-lcd
#include "Drivers/LCD/LCD.h"

#define M_PI 3.141593 
#define PERIOD_MS 500

const volatile extern float kA; // +-2g 10 bits
const volatile extern float kM; // +-4.7G 12 bits

volatile extern float pitch, roll, yaw, angleThen;
//extern float angleThen;

SemaphoreHandle_t IMU_mutex;
SemaphoreHandle_t SW_start_sm, SW_stop_sm;
QueueHandle_t disp_queue;
TaskHandle_t get_handle;

/** BP - Peripheral register structure */
typedef struct Raw {
	// These values are the RAW signed 16-bit readings from the sensors.
	int16_t mx, my, mz; // x, y, and z axis readings of the magnetometer
	int16_t gx, gy, gz; // x, y, and z axis readings of the gyroscope
	int16_t ax, ay, az; // x, y, and z axis readings of the accelerometer
	
} volatile Raw;

Raw Raw_Data;

typedef struct mg_acc {
	float magX, magY, magZ; 
	float accelX, accelY, accelZ; 
	
} volatile mg_acc;

mg_acc Mag_Accel;


void delayUs(int);
void delayMs(int);

#endif /* COMMON_H_ */
