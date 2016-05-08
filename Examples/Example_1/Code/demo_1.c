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
#include "demo_1.h"

// storage for callback.
static void (*TouchCallback)(DEMO_1_EVENTS button) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_1_Screen();
void Demo_1_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_1_Start(void (*touchcallback)(DEMO_1_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_1_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_1_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_1_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D1_BTN_EXIT)
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_1_Screen()
{
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
        CMDText( 10, 50, 30, 0, "Screen: DEMO 1 (primitives)");
        
        DLBegin(PRIMITIVE_POINT);           // *** Green point.
            DLColorRGB(0x00, 0xFF, 0x00);
            DLPointSize(10 * 16);               // Redius = 10 pixels. Remember, point size = 1/16.
            DLVertex2F(20, 100);
        DLBegin(PRIMITIVE_LINE);
            DLColorRGB(0xFF, 0x00, 0x00);   // *** Red line.
            DLLineWidth(5 * 16);                // Width = 5 pixels. Remember, line width = 1/16.
            DLVertex2F(20, 120);
            DLVertex2F((LCDWIDTH - 20), 120);
        DLBegin(PRIMITIVE_LINE_STRIP);      // *** Strip Line.
            DLLineWidth(1 * 16);                // Width = 1 pixel.
            DLColorRGB(0xFF, 0xFF, 0xFF);       // First segment White.
            DLVertex2F(20, 140);            
            DLVertex2F(70, 150);
            DLColorRGB(0xFF, 0x00, 0x00);       // Second segment Red.
            DLVertex2F(120, 140);
            DLColorRGB(0x00, 0xFF, 0x00);
            DLVertex2F(170, 150);               // Third segment Green.
        DLBegin(PRIMITIVE_RECTANGLE);       // *** Rectangle.
            DLColorRGB(0xFF, 0xFF, 0xFF);       // White.
            DLVertex2F(20, 160);
            DLVertex2F(100, 240);
            DLLineWidth(5 * 16);                // Round rectangle.
            DLVertex2F(120, 160);
            DLVertex2F(200, 240);
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D1_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120 - 20, LCDHEIGHT - 50 - 20, 120, 50, 30, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP);        
}

/* [] END OF FILE */
