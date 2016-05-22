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
#include "demo_10.h"
#include "Demos_Resources.h"
#include "..\..\..\PSoC_Eve_Library\PSoCEve_Config.h"

// storage for callback.
static void (*TouchCallback)(DEMO_10_EVENTS button) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_10_Screen();
void Demo_10_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_10_Start(void (*touchcallback)(DEMO_10_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_10_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_10_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_10_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D10_BTN_EXIT)
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_10_Screen()
{
    char rotation = -1;
    unsigned char exit = 0;
    
    while(!exit)
    {
        rotation++;
        
        #if defined EVE_FT800
            if (rotation == 2) 
            {
                rotation = 0;
                exit = 1;
            }
            
            FT_Register_Write(REG_ROTATE, rotation);
        #endif
        
        #if defined EVE_FT810
            if (rotation == 8)
            {
                rotation = 0;
                exit = 1;
            }
            
            FT_ListStart(DLIST);
                CMDSetRotate(rotation);
            FT_ListEnd(END_DL_SWAP);
        #endif    
        
        
        /* Start a new Display List. */
        FT_ListStart(DLIST);

            // Num. format for Vertex2F.
            DLVertexFormat(VERTEX_FORMAT_1);    // 1/1    
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);
            
            // Show top message.
            DLColorRGB(0xFF, 0x00, 0x00);
            CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
            CMDText( 10, 50, 30, 0, "Screen: DEMO 10 (scr rotation)");
            
            DLColorRGB(0x00, 0x00, 0xFF);
            CMDText( 10, 100, 30, 0, "Rotation = ");
            DLColorRGB(0x00, 0xFF, 0x00);
            CMDNumber(170, 100, 30, 0, rotation);
          
            if (exit)
            {
                // Exit button..
                CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
                DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
                DLTag(D10_BTN_EXIT);             // For touch. Assign tag 1 to this button.
                CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            }
            
        /* Finish current display list. Make SWAP. */
        FT_ListEnd(END_DL_SWAP); 
        
        if (!exit) CyDelay(2000);       
   };
}

/* [] END OF FILE */
