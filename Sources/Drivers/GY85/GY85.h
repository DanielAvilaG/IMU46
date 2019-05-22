/*
 * GY85.h
 *
 *  Created on: May 21, 2019
 *      Author: Dani
 */

#ifndef GY85_H_
#define GY85_H_

#include "../../common.h"




void GY85_mag_init(void);
void GY85_acc_init(void);

void GY85_acc_read(void);
void GY85_mag_read(void);

int GY85_test(void);

#endif /* GY85_H_ */
