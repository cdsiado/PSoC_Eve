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
#include "demo_4.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_4_EVENTS event) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_4_Stop();
void Demo_4_Screen();
void Demo_4_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_4_Start(void (*touchcallback)(DEMO_4_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_4_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = Demo_4_Stop;         
    return Demo_4_Loop;
}

/* *** Stop the demo. *********************************************************
*/

void Demo_4_Stop()
{
    // Stop the screen saver.
    FT_ListStart(DLIST);
        CMDStop();
    FT_ListEnd(END_DL_SWAP);
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_4_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D4_EXIT)
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_4_Screen()
{
    unsigned int bitmaplength;
    
    /* Start a new Display List. */
    FT_ListStart(DLIST);
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show logo animation.
        CMDLogo(); 
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP); 
    
    // FT programmer guide says the logo plays during about 2,5 seconds.
    // We wait 3 seconds.
    CyDelay(3000);
    
    // For the screen saver, we use the same bitmap used in previous demo but
    // in zlib compressed format.
    
    bitmaplength = sizeof(testbitmapzlib);
    
    FT_ListStart(DLIST); 
        CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory at offset 0.
        FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
    FT_ListEnd(END_DL_NOSWAP);
    
    FT_ListStart(DLIST); 
    
        CMDScreenSaver();
        
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 4 (Logo & ScreenSaver)");        

        // Restore white color or the bitmap will be tinted with colorRGB.
        DLColorRGB(0xFF, 0xFF, 0xFF);
        DLTag(D4_EXIT);
        DLBegin(PRIMITIVE_BITMAP);        // Start new primitive (BITMAP.
        DLBitmapSource(0x00);             // Source address 0 in RAM_G.
        DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
        DLMacro(0);
    FT_ListEnd(END_DL_SWAP);    
}

/* [] END OF FILE */
