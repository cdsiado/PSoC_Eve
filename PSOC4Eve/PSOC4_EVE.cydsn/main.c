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

    /* Start SPI bus. */
    SPI_EVE_SS_Write(1);
    SPI_EVE_Start();
 
    
    /* Start UART. */
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
//        /* Place your application code here. */
//        if (CurrentScreenTask != 0) (*CurrentScreenTask)();
//        
//        if (newScreen != currentScreen)
//        {
//            switch (newScreen)
//            {
//                case 0: 
//                {
//                    CurrentScreenTask = Screen_0_Create(Screen_0_TouchCallback);
//                }; break;
//                case 1:
//                {
//                    CurrentScreenTask = Screen_1_Create(Screen_1_TouchCallback);
//                }; break;
//            }
//            
//            currentScreen = newScreen;
//        }
    }
}

//void Screen_0_TouchCallback(unsigned char button)
//{
//    if (button == NEXT) newScreen = 1;
//}
//
//void Screen_1_TouchCallback(unsigned char button)
//{
//    if (button == BACK) newScreen = 0;
//    else if (button == NEXT) newScreen = 2;
//}
//
//void Screen_2_TouchCallback(unsigned char button)
//{
//    if (button == BACK) newScreen = 1;
//}
//
//void Screen_1()
//{
//    unsigned long ramDisplayList = RAM_DL;                                              // Set beginning of display list memory.
//    
////    EVE_Memory_Write_Long(ramDisplayList, (DL_CLEAR_COLOR_RGB | RED)); 		                // Clear screen (using background color.  
////    ramDisplayList += 4;
////    EVE_Memory_Write_Long(ramDisplayList, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));    // Clear all.	  															
////    ramDisplayList += 4;										
////    EVE_Memory_Write_Long(ramDisplayList, DL_DISPLAY);			                        // DISPLAY (End of display list)
////    EVE_Memory_Write_Long(REG_DLSWAP, DLSWAP_FRAME);			
////      ramDisplayList = RAM_DL;
////    EVE_Display_ON();
////    EVE_Memory_Write_Byte(REG_PWM_DUTY, 128);	
//}
////
////void Screen_2()
////{
////    unsigned long ramDisplayList = RAM_DL;                                              // Set beginning of display list memory.
////    
////    EVE_Memory_Write_Long(ramDisplayList, (DL_CLEAR_RGB | BLACK)); 		                // Clear screen (using background color.  
////    ramDisplayList += 4;
////    EVE_Memory_Write_Long(ramDisplayList, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));    // Clear all.	  															
////    ramDisplayList += 4;										
////    EVE_Memory_Write_Long(ramDisplayList, DL_DISPLAY);			                        // DISPLAY (End of display list)
////    EVE_Memory_Write_Long(REG_DLSWAP, DLSWAP_FRAME);
////}
////
//void Screen_3()
//{
//    EVE_Touch_Enable();
//    EVE_Touch_Calibrate();    
//}

/* [] END OF FILE */
