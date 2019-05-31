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
#include "EInt1.h"
#include "ExtIntLdd1.h"
#include "EInt2.h"
#include "ExtIntLdd2.h"
#include "LED2.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "PTC.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */



#include "common.h"
#include "wrappers.h"





static portTASK_FUNCTION(IMU_get_values, pvParameters){
	(void) pvParameters;
	while (pdTRUE)
	{
		read_RTOS();
	}
}


static portTASK_FUNCTION(IMU_proccess_values, pvParameters){
	(void) pvParameters;

	while (pdTRUE) 
	{
		proccess_RTOS();
	}
}

static portTASK_FUNCTION(DISP_angle, pvParameters){
	(void) pvParameters;
	char buffer[4];
	while (pdTRUE) 
	{
		xQueueReceive( disp_queue, buffer, portMAX_DELAY );
		vfnLCD_Write_Msg((uint8 *)buffer);
	}
}





/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  Cpu_EnableInt();
  /*** End of Processor Expert internal initialization.                    ***/
  /* Write your code here */
  /* For example: for(;;) { } */
	UART0_init();
	I2C1_init();
	#ifdef GY85
		GY85_mag_init();
		GY85_acc_init();
	#endif
	#ifdef LSM9DS1
		
	#endif
	
	char buffer[4];
	sprintf(buffer, "%04i", 1234);
	vfnLCD_Write_Msg((uint8 *)buffer);
	
	/* Create mutex */
	example_mutex = xSemaphoreCreateMutex();
	disp_queue = xQueueCreate( 4,4*sizeof(char));
	//for(;;) 
		//GY85_test();
	//LSM9DS1_mag_read();
	//for(;;) HMC();
	if( example_mutex != NULL && disp_queue != NULL) {
		(void) FRTOS1_xTaskCreate(IMU_get_values, (portCHAR *)"IMU_get_values", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
		(void) FRTOS1_xTaskCreate( DISP_angle, ( portCHAR * ) "DISP_angle", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL );
		(void) FRTOS1_xTaskCreate(IMU_proccess_values, (portCHAR *)"IMU_proccess_values", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
	}
	
 

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
