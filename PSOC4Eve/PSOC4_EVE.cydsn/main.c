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
//#include "..\..\EVE_Library.cylib\PSOC_EVE.h"

#include "..\..\PSoCEveLibrary\PsoCEve.h"
#include "Test.h"

// AN_312 Colors - fully saturated colors defined here
#define RED					0xFF0000UL													// Red
#define GREEN				0x00FF00UL													// Green
#define BLUE				0x0000FFUL													// Blue
#define WHITE				0xFFFFFFUL													// White
#define BLACK				0x000000UL

#define delayTime 3000

int main()
{
    unsigned int cmdBufferRd = 0x0000;
    unsigned int cmdBufferWr = 0x0000;          // Used to navigate command ring buffer
unsigned int cmdOffset = 0x0000;
    unsigned long color;
    unsigned int point_size = 0x0100;           // Define a default dot size
unsigned long point_x = (96 * 16);              // Define a default point x-location (1/16 anti-aliased)
unsigned long point_y = (136 * 16);             // Define a default point y-location (1/16 anti-aliased)
	unsigned long ramDisplayList = RAM_DL;      // Set beginning of display list memory.
    unsigned char gpio;


    
    int duty;
    /* Start SPI bus. */
    SPI_EVE_SS_Write(1);
    SPI_EVE_Start();
 
    
    /* Start UART. */
   	UART_Start();
    UART_UartPutString("\n\r");
	UART_UartPutString("*** EVE TEST ***\n\r");
	UART_UartPutString("----------------\n\r");
	UART_UartPutString("\n\r");
    

    
    /* Initialize LCD Display. */
    if (!EVE_Init_Display())
    {
        // error.
    }
    
    //***************************************
    // Configure Touch and Audio - not used in this example, so disable both
    
    mEVE_Register_Write(REG_TOUCH_MODE, ZERO);        // Disable touch
    mEVE_Register_Write(REG_TOUCH_RZTHRESH, ZERO);    // Eliminate any false touches

    mEVE_Register_Write(REG_VOL_PB, ZERO);            // turn recorded audio volume down
    mEVE_Register_Write(REG_VOL_SOUND, ZERO);         // turn synthesizer volume down
    mEVE_Register_Write(REG_SOUND, 0x6000);           // set synthesizer to mute

    // End of Configure Touch and Audio
    //***************************************    

  //  while (1);
    //EVE_Touch_Enable();
    
        T_Init();
    
    TouchCalibrationValues calibrationvalues = { .TouchTransform_Bytes = {0x2E, 0x83, 0x00, 0x00, 0x0D, 0x02, 0x00, 0x00, 0xF0, 0xDF, 0xE3, 0xFF,
                                                                          0x6E, 0x00, 0x00, 0x00, 0x66, 0xB3, 0xFF, 0xFF, 0x47, 0xE9, 0x1D, 0x01} };
    
    FT_Touch_Enable();
    //FT_Touch_Calibrate();
    //FT_Touch_ReadCalibrationValues(&calibrationvalues);
    FT_Touch_WriteCalibrationValues(&calibrationvalues);

    
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
    T_DL_TAG_AND_MASK();
    while(1);
//    /* *** COPROCESSOR *** */
//    T_CMD_GRADIENT();
//    CyDelay(delayTime);
//    T_CMD_TEXT();
//    CyDelay(delayTime);
//    T_CMD_BUTTON();
//    CyDelay(delayTime);
//    T_CMD_KEYS();
//    CyDelay(delayTime);
//    T_CMD_PROGRESS();
//    CyDelay(delayTime);
//    T_CMD_SLIDER();
//    CyDelay(delayTime);
//    T_CMD_SCROLLBAR();
//    CyDelay(delayTime);
//    T_CMD_TOGGLE();
//    CyDelay(delayTime);
//    T_CMD_GAUGE();
//    CyDelay(delayTime);
//    T_CMD_CLOCK();
//    CyDelay(delayTime);
//    T_CMD_CALIBRATE();
//    CyDelay(delayTime);
//    T_CMD_SPINNER();
//    CyDelay(delayTime);
//    T_CMD_DIAL();
//    CyDelay(delayTime);
//    T_CMD_NUMBER();
//    CyDelay(delayTime);
//    T_CMD_SKETCH();
//    CyDelay(delayTime);
//    T_CMD_LOGO();
//    CyDelay(delayTime);
    T_CMD_SCREENSAVER();
    CyDelay(delayTime);
    T_CMD_INFLATE();
    
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
