/*
 * LSM9DS1.h
 *
 *  Created on: May 17, 2019
 *      Author: Dani
 */

#ifndef LSM9DS1_H_
#define LSM9DS1_H_

//#include <stdio.h>
#include "../../MKL46Z4.h"
#include "../../common.h"
#include "LSM9DS1_Registers.h"



void LSM9DS1_mag_read(void);
void LSM9DS1_acc_read(void);
int LSM9DS1_test(void);




#endif /* LSM9DS1_H_ */
