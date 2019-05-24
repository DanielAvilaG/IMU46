/*
 * common.c
 *
 *  Created on: May 22, 2019
 *      Author: Dani
 */



/* delay n microseconds
* The CPU core clock is set to MCGFLLCLK at 41.94 MHz in SystemInit().
*/
void delayUs(int n)
{
	int i; int j;
	for(i = 0 ; i < n; i++) {
		for(j = 0; j < 7; j++) ;
	}
}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
		for (j = 0; j < 7000; j++) {}
}
