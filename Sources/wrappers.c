/*
 * wrappers.c
 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */


#include "wrappers.h"

volatile float pitch = 0.0, roll = 0.0, yaw = 0.0;

const volatile float kA = 1/256.00; // +-2g 10 bits
const volatile float kM = 1/390.00; // +-4.7G 12 bits

void GY85_read_RTOS()
{
	if (xSemaphoreTake(example_mutex, portMAX_DELAY)) 
	{
		LED1_Neg();
		//taskYIELD();
		
		//GY85_mag_read();
		//GY85_acc_read();
		
		LSM9DS1_mag_read();
		
		xSemaphoreGive(example_mutex);
		vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void proccess_RTOS()
{
	char buffer[40];
	char buffer1[4];

	if (xSemaphoreTake(example_mutex, portMAX_DELAY)) 
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
		float angulo = 180 * atan2((int)Raw_Data.mx, (int)Raw_Data.my) / M_PI;
		int p = round(pitch), r = round(roll), y = round(yaw), a = round(angulo)+180 % 360;
		int a1 = a;
		sprintf(buffer1, "%04i", a1);
		vfnLCD_Write_Msg((uint8 *)buffer1);
		sprintf(buffer,"PITCH: %d -- ROLL: %d -- YAW: %d -- Angulo: %d", p, r, y, a);
		UART0_send_string_ln(buffer);
		xSemaphoreGive(example_mutex);
		FRTOS1_vTaskDelay(pdMS_TO_TICKS(600));
	}
}

