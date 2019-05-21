/* ###################################################################
**     Filename    : main.c
**     Project     : IMU46
**     Processor   : MKL46Z256VMC4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2019-05-16, 19:02, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "FRTOS1.h"
#include "MCUC1.h"
#include "UTIL1.h"
#include "LED1.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "SegLCD1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */
#include <math.h>
#include <stdio.h>

#include "wrappers.h"

#include "MKL46Z4.h"

#include "Drivers/I2C/I2C.h"

#include "Drivers/UART/UART.h"

// #include "Drivers/LSM9DS1/LSM9DS1.h"
#include "Drivers/GY85/GY85.h"

// http://bit.do/KL46z-lcd
#include "Drivers/LCD/LCD.h"

//static volatile int i = 0;
static portTASK_FUNCTION(IMU_get_values, pvParameters){
	(void) pvParameters;
	char buffer[4];
	for(;;){
		LED1_Neg();
		
		//LSM9DS1_mag_read();
		//buffer[0]= Raw_Data.mx;
		//buffer[5]='\0';
		//sprintf(buffer,"-- MagX: %d -- MagY: %d -- MagZ: %d", Raw_Data.mx, Raw_Data.my, Raw_Data.mz);
		//UART0_send_string_ln(Raw_Data.mx);

		GY85_read_RTOS();
		
		sprintf(buffer, "%04i", Raw_Data.mx);
		//i = (i+1) % 10000;
		vfnLCD_Write_Msg((uint8 *)buffer);
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	}
}

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


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
	UART0_init();
	I2C1_init();
	GY85_mag_init();
	GY85_acc_init();
	char buffer[4];
	sprintf(buffer, "%04i", 1234);
	vfnLCD_Write_Msg((uint8 *)buffer);
	//for(;;) 
		//GY85_test();
	//LSM9DS1_mag_read();
	//for(;;) HMC();
  (void) FRTOS1_xTaskCreate(IMU_get_values, (portCHAR *)"IMU_get_values", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
