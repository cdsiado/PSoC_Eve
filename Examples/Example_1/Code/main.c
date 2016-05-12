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

/* Include PSoC_Eve library header file. */
#include "..\..\..\PSoC_Eve_Library\PsoCEve.h"


/* Include a header file for every demo. */
#include "demo_0.h"
#include "demo_1.h"
#include "demo_2.h"
#include "demo_3.h"
#include "demo_4.h"
#include "demo_5.h"
#include "demo_6.h"
#include "demo_7.h"

#define delayTime 3000

enum DEMOS { NODEMO, DEMO_0, DEMO_1, DEMO_2, DEMO_3, DEMO_4, DEMO_5, DEMO_6, DEMO_7 };

unsigned char currentDemo = NODEMO;
unsigned char newDemo = NODEMO;

void Demo_0_TouchCallback(DEMO_0_EVENTS event);
void Demo_1_TouchCallback(DEMO_1_EVENTS event);
void Demo_2_TouchCallback(DEMO_2_EVENTS event);
void Demo_3_TouchCallback(DEMO_3_EVENTS event);
void Demo_4_TouchCallback(DEMO_4_EVENTS event);
void Demo_5_TouchCallback(DEMO_5_EVENTS event);
void Demo_6_TouchCallback(DEMO_6_EVENTS event);
void Demo_7_TouchCallback(DEMO_7_EVENTS event);

void (*CurrentScreenLoop)() = 0;
void (*CurrentScreenCloseFunction)() = 0;

/* Function prototypes. */

void CalibrateTouchPanel();

int main()
{
    /* Storage for calibration values. */
    TouchCalibrationValues calibrationvalues;
    
    /* *** Start SPI bus. ***************************************************** 
        In schematic, SPI module is configured to have one SS line.
        PSoC Eve library doesnÂ´t initialize SPI bus.
        User is responsible of SPI component initialization and SS signal initialization.
    */

    SPI_Start();
    SPI_SS_Write(1);
    
    /* *** Initialize LCD Display. ********************************************
        If initialization fails, program gets locked. 
    */
    if (!FT_Init())
    {
        while(1);
    }
    
    /* *** Turn ON the display.
        Set backlight PWM duty cycle.
    */
    FT_Display_ON();
    FT_Register_Write(REG_PWM_DUTY, 128);
    
    /* *** We will use the touch panel, enable it. ****************************
    */
    FT_Touch_Enable();
    
    /* *** Turn on audio. Max volume.
    */
    FT_Audio_Unmute();
    FT_Sound_Volume(255);
    
    /* *** Calibration. *******************************************************
        In this demo, every time the app starts it performs calibration.
        Remember that FT chip loose calibration values every time it is powered off,
        the user is responsible of storing calibration values in microcontroller flash
        memory or in other external memory.
    */
    
    CalibrateTouchPanel();                                  // Perform calibration. 
        // After calibration, we read calibration values from FT chip.
        // We can store contents of 'calibrationvalues.TouchTransform_Bytes' in memory 
        // (flash, external, etc...) to 
        // avoid to perform calibration every time we turn on the system.
        // In this demo, values are not saved in memory.
    FT_Touch_ReadCalibrationValues(&calibrationvalues);     
    
        // Write calibration value to FT chip.
        // Yes, the same value we have readed previously. This is not needed here, it is
        // only for demo purpouses; to show you how to write cal values to FT chip.
        /* This comment block, shows you a posible initialization of calibration values.
           
            TouchCalibrationValues calibrationvalues = { .TouchTransform_Bytes = {0x2E, 0x83, 0x00, 0x00, 0x0D, 0x02, 0x00, 0x00, 0xF0, 0xDF, 0xE3, 0xFF,
                                                                                  0x6E, 0x00, 0x00, 0x00, 0x66, 0xB3, 0xFF, 0xFF, 0x47, 0xE9, 0x1D, 0x01} };
    
            You can write a function to initialize this values with data previously stored in flash or
            external memory.
        */
    FT_Touch_WriteCalibrationValues(&calibrationvalues);    // Write calibration values to FT chip.
        
    
    /* *** Show main screen. **************************************************
    */
    CurrentScreenLoop = Demo_0_Start(Demo_0_TouchCallback, &CurrentScreenCloseFunction);
    currentDemo = newDemo = DEMO_0;
    
    // * PROGRAM MAIN LOOP ****************************************************

    /* CyGlobalIntEnable; */
    for(;;)
    {
        // Call current demo main loop.
        if (CurrentScreenLoop != 0) (*CurrentScreenLoop)();
        
        // Check if we have to change to other demo.
        if (newDemo != currentDemo)
        {
            /* Call closing function of current demo. */
            if (CurrentScreenCloseFunction != 0) (*CurrentScreenCloseFunction)();
            
            /* Call start function of new demo. */
            switch(newDemo)
            {
                case DEMO_0: 
                {
                    CurrentScreenLoop = Demo_0_Start(Demo_0_TouchCallback, &CurrentScreenCloseFunction);
                }; break;
                
                case DEMO_1: 
                {
                    CurrentScreenLoop = Demo_1_Start(Demo_1_TouchCallback, &CurrentScreenCloseFunction);
                }; break;
                
                case DEMO_2: 
                {
                    CurrentScreenLoop = Demo_2_Start(Demo_2_TouchCallback, &CurrentScreenCloseFunction);
                }; break;    
                
                case DEMO_3: 
                {
                    CurrentScreenLoop = Demo_3_Start(Demo_3_TouchCallback, &CurrentScreenCloseFunction);
                }; break;   
                
                case DEMO_4: 
                {
                    CurrentScreenLoop = Demo_4_Start(Demo_4_TouchCallback, &CurrentScreenCloseFunction);
                }; break;   
                
                case DEMO_5: 
                {
                    CurrentScreenLoop = Demo_5_Start(Demo_5_TouchCallback, &CurrentScreenCloseFunction);
                }; break;    
                
                case DEMO_6: 
                {
                    CurrentScreenLoop = Demo_6_Start(Demo_6_TouchCallback, &CurrentScreenCloseFunction);
                }; break;   
                
                case DEMO_7: 
                {
                    CurrentScreenLoop = Demo_7_Start(Demo_7_TouchCallback, &CurrentScreenCloseFunction);
                }; break;                   
            }
            
            /***/
            currentDemo = newDemo;
        }

    }    
 
}

/* *** Calibration of the touch panel.
*/
void CalibrateTouchPanel()
{
    /* Start a display list. */    
    FT_ListStart(DLIST);
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show message for calibration.
        // Place the message at the center of the display an use centering options.
        DLColorRGB(0xFF, 0xFF, 0xFF);
        CMDText(LCDWIDTH / 2, LCDHEIGHT / 2, 28, OPT_CENTERX | OPT_CENTERY, "Please tap on every dot.");
    
        // Call calibration command.
        CMDCalibrate();
        
    /* Finish the list. Swap to show the message. */
    FT_ListEnd(END_DL_NOSWAP);  
    
    /* Coprocesor will be busy until the calibration procedure ends.
       Then, wait until coprocessor is ready. */
    while (!FTIsCoproccesorReady()) {};
}

/* *** Callback function for DEMO 0. ******************************************
*/
void Demo_0_TouchCallback(DEMO_0_EVENTS event)
{
    // For Demo 0, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D0_BTN_DEMO_1: // Demo 1 button pressed.
            newDemo = DEMO_1; break;
        case D0_BTN_DEMO_2: // Demo 2 button pressed.
            newDemo = DEMO_2; break;
        case D0_BTN_DEMO_3: // Demo 3 button pressed.
            newDemo = DEMO_3; break;   
        case D0_BTN_DEMO_4: // Demo 4 button pressed.
            newDemo = DEMO_4; break;  
        case D0_BTN_DEMO_5: // Demo 5 button pressed.
            newDemo = DEMO_5; break;
        case D0_BTN_DEMO_6: // Demo 6 button pressed.
            newDemo = DEMO_6; break;  
        case D0_BTN_DEMO_7: // Demo 6 button pressed.
            newDemo = DEMO_7; break;         
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 1. ******************************************
*/
void Demo_1_TouchCallback(DEMO_1_EVENTS event)
{
    // For Demo 1, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D1_BTN_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 2. ******************************************
*/
void Demo_2_TouchCallback(DEMO_2_EVENTS event)
{
    // For Demo 2, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D2_BTN_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 3. ******************************************
*/
void Demo_3_TouchCallback(DEMO_3_EVENTS event)
{
    // For Demo 3, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D3_BTN_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 4. ******************************************
*/
void Demo_4_TouchCallback(DEMO_4_EVENTS event)
{
    // For Demo 4, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D4_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 5. ******************************************
*/
void Demo_5_TouchCallback(DEMO_5_EVENTS event)
{
    // For Demo 5, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D5_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 6. ******************************************
*/
void Demo_6_TouchCallback(DEMO_6_EVENTS event)
{
    // For Demo 6, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D6_BTN_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* *** Callback function for DEMO 7. ******************************************
*/
void Demo_7_TouchCallback(DEMO_7_EVENTS event)
{
    // For Demo 7, 'event' contains the value of the pressed button.
    switch(event)
    {
        case D7_BTN_EXIT: // Exit button pressed.
            newDemo = DEMO_0; break;
    }
    
    FT_Sound_Play(0x50, 0xc0);
}

/* [] END OF FILE */
