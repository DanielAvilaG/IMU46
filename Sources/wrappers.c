/*
 * wrappers.c
 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */


#include "wrappers.h"

volatile float pitch = 0.0, roll = 0.0, yaw = 0.0, angleThen = 0.0;


#ifdef GY85
	const volatile float kA = 1/256.00; // +-2g 10 bits
	const volatile float kM = 1/390.00; // +-4.7G 12 bits
#endif
#ifdef LSM9DS1
	const volatile float kA = 0.122; // +-4g 
	const volatile float kM = 0.14; // +-4G 
#endif

void read_RTOS()
{
	if (xSemaphoreTake(IMU_mutex, portMAX_DELAY)) 
	{
		
		//LED2_Neg();
		//taskYIELD();
		#ifdef GY85
			GY85_mag_read();
			GY85_acc_read();
		#endif
		#ifdef LSM9DS1
			LSM9DS1_mag_read();
			LSM9DS1_acc_read();
		#endif

		xSemaphoreGive(IMU_mutex);
	}
}

void proccess_RTOS()
{
	char buffer1[4] = {'<'};

	if (xSemaphoreTake(IMU_mutex, portMAX_DELAY)) 
	{
		Mag_Accel.accelX = Raw_Data.ax*kA;
		Mag_Accel.accelY = Raw_Data.ay*kA;
		Mag_Accel.accelZ = Raw_Data.az*kA;
		
		Mag_Accel.magX = Raw_Data.mx*kM;
		Mag_Accel.magY = Raw_Data.my*kM;
		Mag_Accel.magZ = Raw_Data.mz*kM;
		
		pitch = 180 * atan2(Mag_Accel.accelX, sqrt(Mag_Accel.accelY*Mag_Accel.accelY + Mag_Accel.accelZ*Mag_Accel.accelZ))/M_PI;
		roll = 180 * atan2(Mag_Accel.accelY, sqrt(Mag_Accel.accelX*Mag_Accel.accelX + Mag_Accel.accelZ*Mag_Accel.accelZ))/M_PI;
		double mag_x = Mag_Accel.magX*cos(pitch) + Mag_Accel.magY*sin(roll)*sin(pitch) + Mag_Accel.magZ*cos(roll)*sin(pitch);
		double mag_y = Mag_Accel.magY * cos(roll) - Mag_Accel.magZ * sin(roll);
		yaw = 180 * atan2(-mag_y,mag_x)/M_PI;
		float angle = (180 * atan2(Raw_Data.mx, Raw_Data.my) / M_PI) + 180 - angleThen;
		int a = round(angle);
		int a1 = (a+360)%360;
		sprintf(&buffer1[1], "%03i", a1);
		xQueueSend( disp_queue, buffer1, 0 );
		
#ifdef DEBUG
		char buffer[40];
		int p = round(pitch), y = round(yaw), r = round(roll);
		sprintf(buffer,"PITCH: %d -- ROLL: %d -- YAW: %d -- Angulo: %d", p, r, y, a);
		UART0_send_string_ln(buffer);
#endif
		xSemaphoreGive(IMU_mutex);
	}
}

