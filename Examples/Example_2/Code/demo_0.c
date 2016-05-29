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
#include "demo_0.h"

// storage for callback.
static void (*TouchCallback)(DEMO_0_EVENTS button) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_0_Screen();
void Demo_0_Loop(); 
void Demo_0_Paint();

/* *** Demo initialization. ***************************************************
*/
void* Demo_0_Start(void (*touchcallback)(DEMO_0_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_0_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_0_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_0_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if ((rdtag > 0) && (rdtag < 9))
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_0_Screen()
{
    /* Start a new Display List. */
    FT_ListStart(DLIST);
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 0");
        
        // First button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(1);                       // For touch. Assign tag 1 to this button.
        CMDButton(10, 100, 100, 50, 28, OPT_3D, (char*)"Demo 1");
        DLTag(2);                       // ... next button... next tag.
        CMDButton(125, 100, 100, 50, 28, OPT_3D, (char*)"Demo 2");
/*        DLTag(3);                       // ... next button... next tag.
        CMDButton(240, 100, 100, 50, 28, OPT_3D, (char*)"Demo 3");
        DLTag(4);                       // ... next button... next tag.
        CMDButton(360, 100, 100, 50, 28, OPT_3D, (char*)"Demo 4");
        DLTag(5);                       // ... next button... next tag.
        CMDButton(10, 170, 100, 50, 28, OPT_3D, (char*)"Demo 5");
        DLTag(6);                       // ... next button... next tag.
        CMDButton(125, 170, 100, 50, 28, OPT_3D, (char*)"Demo 6");    
        DLTag(7);                       // ... next button... next tag.
        CMDButton(240, 170, 100, 50, 28, OPT_3D, (char*)"Demo 7");  
        DLTag(8);                       // ... next button... next tag.
        CMDButton(360, 170, 100, 50, 28, OPT_3D, (char*)"Demo 8");        
       */ 
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP);        
}

/* [] END OF FILE */
