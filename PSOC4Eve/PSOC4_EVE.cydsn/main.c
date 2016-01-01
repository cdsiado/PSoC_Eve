/*******************************************************************************
* File Name: main.c  
* Version 0.1 Alpha
*
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#include <project.h>

#include "..\..\PSoCEveLibrary\PsoCEve.h"
#include "Test.h"

#define delayTime 3000

int main()
{
    /* *** Start SPI bus. *** 
        In schematic, SPI module is configured to have one SS line.
        Disconects SS0 from HSIOM so it can be controlled by software instead of hardware or API. */

    SPI_Start();
    
    (*(reg32 *)SPI_ss0_m__0__HSIOM) = 
        ((*(reg32 *)SPI_ss0_m__0__HSIOM) & (uint32)~SPI_ss0_m__0__HSIOM_MASK) | (uint32)(SPI_HSIOM_GPIO_SEL << SPI_ss0_m__0__HSIOM_SHIFT);
    
    SPI_ss0_m_Write(1); 
 
    
    /* *** Start UART. *** */
   	UART_Start();
    UART_UartPutString("\n\r");
	UART_UartPutString("*** EVE TEST ***\n\r");
	UART_UartPutString("----------------\n\r");
	UART_UartPutString("\n\r");
        
    /* Initialize LCD Display. If initialization fails, program gets locked. */
    if (!FT_Init())
    {
        while(1);
    }
   
    /* Initialize test. This enables display. */
    T_Init();
    
    
    /* About calibration and calibration values.
       Every time the FT chip is powered on, default calibration values are not proper values so
       it needs to be calibrated. And then, calibration values are lost when the FT chip is powered off.
        
       This is a test program during the library development, so, actually there is not a function that
       store calibration values to flash rom.
       First time i run the program, i commented line "FT_Touch_WriteCalibrationValues" and 
       uncommented lines "FT_Touch_Calibrate" and "FT_Touch_ReadCalibrationValues".
       Then, placed a breakpoint in line "while(1)"; and debbuged the program. After calibration, and
       after line "FT_Touch_ReadCalibrationValues" i took calibration values by hand.
       Those are the values i am using actually for "calibrationvalues" initialization.
    
       Storing calibration values in flash rom is planned.
    */
    
    
    
    /* Initialize touch calibration values. */
    TouchCalibrationValues calibrationvalues = { .TouchTransform_Bytes = {0x2E, 0x83, 0x00, 0x00, 0x0D, 0x02, 0x00, 0x00, 0xF0, 0xDF, 0xE3, 0xFF,
                                                                          0x6E, 0x00, 0x00, 0x00, 0x66, 0xB3, 0xFF, 0xFF, 0x47, 0xE9, 0x1D, 0x01} };

    FT_Touch_Enable();                                      // Enable touch panel.
    FT_Touch_WriteCalibrationValues(&calibrationvalues);    // Write calibration values to FT chip.   
    //FT_Touch_Calibrate();                                   // Touch calibration procedure.                 
    //FT_Touch_ReadCalibrationValues(&calibrationvalues);     // Read calibration values.
    //while(1);


    
    /* *** DISPLAY LIST *** */
//    T_DL_A();
//    CyDelay(delayTime);
//    T_DL_PRIMITIVE_POINT();
//    CyDelay(delayTime);
//    T_DL_PRIMITIVE_LINE();
//    CyDelay(delayTime);
//    T_PRIMITIVE_EDGESTRIP();
//    CyDelay(delayTime);
//    T_PRIMITIVE_RECTANGLE();
//    CyDelay(delayTime);
//    T_PRIMITIVE_BITMAP();
//    CyDelay(delayTime);
//    T_DL_B();
//    CyDelay(delayTime);
//    T_DL_SCISSOR();
//    CyDelay(delayTime);
//    T_CMD_CALIBRATE();
//    CyDelay(delayTime);
//    T_DL_TAG_AND_MASK();
//    while(1);
    
    /* *** COPROCESSOR *** */
    T_CMD_GRADIENT();
    CyDelay(delayTime);
    T_CMD_TEXT();
    CyDelay(delayTime);
    T_CMD_BUTTON();
    CyDelay(delayTime);
    T_CMD_KEYS();
    CyDelay(delayTime);
    T_CMD_PROGRESS();
    CyDelay(delayTime);
    T_CMD_SLIDER();
    CyDelay(delayTime);
    T_CMD_SCROLLBAR();
    CyDelay(delayTime);
    T_CMD_TOGGLE();
    CyDelay(delayTime);
    T_CMD_GAUGE();
    CyDelay(delayTime);
    T_CMD_CLOCK();
    CyDelay(delayTime);
    T_CMD_CALIBRATE();
    CyDelay(delayTime);
    T_CMD_SPINNER();
    CyDelay(delayTime);
    T_CMD_DIAL();
    CyDelay(delayTime);
    T_CMD_NUMBER();
    CyDelay(delayTime);
    T_CMD_SKETCH();
    CyDelay(delayTime);
    T_CMD_LOGO();
    CyDelay(delayTime);
    T_CMD_SCREENSAVER();
    CyDelay(delayTime);
    T_CMD_INFLATE();
    CyDelay(delayTime);
    T_SOUND();
    
    while(1);

    // ************************************************************************

    /* CyGlobalIntEnable; */
    for(;;)
    {
    }
}



/* [] END OF FILE */
