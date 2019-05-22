/*
 * wrappers.c
 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */


#include "wrappers.h"

void GY85_read_RTOS()
{
	GY85_mag_read();
	GY85_acc_read();
}

