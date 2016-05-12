/*******************************************************************************
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015, 2016 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#include <project.h>

#include "..\..\..\PSoC_Eve_Library\PsoCEve.h"
#include "..\..\..\PSoC_Eve_Library\PsoCEve_Config.h"
#include "demo_6.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_6_EVENTS event) = 0;

/* *** Function prototypes. ***************************************************
*/

void Demo_6_Screen();
void Demo_6_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_6_Start(void (*touchcallback)(DEMO_6_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_6_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = 0;         
    return Demo_6_Loop;
}


/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_6_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D6_BTN_EXIT)
    {
        (*TouchCallback)(rdtag);
    }
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_6_Screen()
{
    uint32 tnumber = 2016;
    
    FT_ListStart(DLIST); 
        
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 6 (Widgets)");
        
        CMDBgcolor(0x00, 0x00, 0xFF);
        DLColorRGB(0xFF, 0xFF, 0xFF);
        CMDFgcolor(0xFF, 0xFF, 0x00);
        
        // Progress bar.
        CMDProgressBar(30, 100, 150, 20, 0, 50, 100);
        // Scroll bar.
        CMDScrollBar(30, 150, 150, 20, 0, 50, 10, 100);
        // Toggle
        CMDToggle(30, 200, 100, 28, 0, TOGGLE_STATE_OFF, "ON" "\xFF" "OFF");
        // Gauge
        CMDGauge(250, 150, 50, 0, 5, 4, 30, 100);
        // Clock
        CMDClock(370, 150, 50, 0, 8, 15, 0, 0);
        
        // Number & Setbase
        // If FT800, only shows the number in decimal base.
        // If FT810, shows the number in decimal, binary and hexadecimal.
        CMDNumber(250, 210, 28, 0, tnumber);
        
#if defined EVE_FT810
        CMDSetBase(NUMBER_BASE_BINARY);
        CMDNumber(250, 230, 28, 0, tnumber);
        CMDSetBase(NUMBER_BASE_HEXADECIMAL);
        CMDNumber(250, 250, 28, 0, tnumber);
#endif    
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D6_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120 - 20, LCDHEIGHT - 50 - 20, 120, 50, 30, OPT_3D, (char*)"Exit");
        
    FT_ListEnd(END_DL_SWAP);    
}

/* [] END OF FILE */
