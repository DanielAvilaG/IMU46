/*
 * LED_25.h
 *
 *  Created on: Apr 27, 2019
 *      Author: Dani
 */

#ifndef LED_25_H_
#define LED_25_H_

//#include "derivative.h" /* include peripheral declarations */
#include "../../MKL46Z4.h"
void RLED25_init(void);
void RLED25_toggle(void);

void GLED25_init(void);
void GLED25_toggle(void);
void GLED25_off(void);

void BLED25_init(void);
void BLED25_toggle(void);
void BLED25_on(void);
void BLED25_off(void);

#endif /* LED_25_H_ */
