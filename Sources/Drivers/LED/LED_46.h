/*
 * LED_46.h
 *
 *  Created on: Apr 7, 2019
 *      Author: PCO
 */

#ifndef LED_46_H_
#define LED_46_H_

#include "../../MKL46Z4.h" /* include peripheral declarations */

void RLED46_init(void);
void RLED46_toggle(void);
void RLED46_off(void);
void RLED46_on(void);

void GLED46_init(void);
void GLED46_toggle(void);
void GLED46_off(void);
void GLED46_on(void);

#endif /* LED_46_H_ */
