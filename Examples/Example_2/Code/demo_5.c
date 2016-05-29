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
#include "demo_5.h"

// storage for callback.
static void (*TouchCallback)(DEMO_5_EVENTS event) = 0;

/* *** Variables. ***************************************************
*/
uint32 tracker, color = 0;
uint16 val = 32768;
uint8 tag = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_5_Screen();
void Demo_5_Loop();

/* *** Demo initialization. ***************************************************
*/
void* Demo_5_Start(void (*touchcallback)(DEMO_5_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_5_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = 0;         
    return Demo_5_Loop;               
}


/* *** Paint contents of screen. **********************************************
*/

void Demo_5_Screen()
{
    tracker = color = tag = 0;
    val = 32768;
    
    //  *** Set the bitmap properties , sketch properties and Tracker for the sliders.
    FT_ListStart(DLIST);

    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 5 (Sketch)");    
    
        // The tracker.
        CMDFgcolor(0xFF, 0xFF, 0xFF);
        CMDTrack(LCDWIDTH - 30, 40, 8, LCDHEIGHT - 100, 207);
        
        // Sketch.
        CMDSketch(0, 100, LCDWIDTH - 40, LCDHEIGHT - 30, 0, BITMAP_LAYOUT_L8);
        CMDMemZero(0, (LCDWIDTH - 40) * (LCDHEIGHT - 20));
        DLBitmapHandle(1);
        DLBitmapSource(0);
        DLBitmapLayout(BITMAP_LAYOUT_L8, LCDWIDTH - 40, LCDHEIGHT - 20);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, LCDWIDTH - 40, LCDHEIGHT - 20);

    FT_ListEnd(END_DL_SWAP);    
}

/* **** Main loop
*/
void Demo_5_Loop()
{

    // Check tracker & compute  color from tracker.
    tracker = FT_Register_Read(REG_TRACKER);
    
    if ((tracker & 0xFF) == 207) 
        val = tracker >> 16;
    
    color = val * 255;
            
    // Check the tag.
    tag = FT_Register_Read(REG_TOUCH_TAG);
    
    if (tag == 206)                 // Clear button.
    {
        FT_ListStart(DLIST);
            CMDMemZero(0, (LCDWIDTH - 40) * (LCDHEIGHT - 20));
        FT_ListEnd(END_DL_SWAP);
    }
    else if (tag == D5_EXIT)        // Exit button.
    {
        (*TouchCallback)(D5_EXIT);
    }

    // Start new display list.
    FT_ListStart(DLIST);
        
        // Num. format for Vertex2F.
        DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 0, 0);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 5 (Sketch)");        

        DLColorRGB(255, 255, 255);
        CMDBgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
        DLLineWidth(1 * 16);
        
        // Sketch background.
        DLBegin(PRIMITIVE_RECTANGLE);
            DLColorRGB(0xFF, 0xFF, 0xFF);
            DLVertex2F(0, 100);
            DLVertex2F(LCDWIDTH - 40, LCDHEIGHT - 20);
	    
        // Drawing color.
        DLColorRGB((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
        
        if (tag == 206)
            CMDFgcolor(0x00, 0x00, 0xFF);
        else
            CMDFgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));

        // Display the a Bitmap.
        // Bitmap handle is 1, and cell = 0. 
        // We are copying the bitmap from RAM_G to the display.
        // Skecth command draws in memory, no in display. Do you understandt??
        DLBegin(PRIMITIVE_BITMAP);
            DLVertex2II(0, 100, 1, 0);
        DLEnd();                        // End the previous begin.
                                        // Realize that this is the first time we use DLEnd in this demo
                                        // demo program.
                                        // It looks that DLEnd is not mandatory.

        // Enable tags.
        DLTagMask(1);
        
        // Draw the slider. Assign tag 207.
        DLTag(207);
        CMDFgcolor(0xFF, 0xFF, 0xFF);
        DLColorRGB((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
        CMDBgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
        CMDSlider(LCDWIDTH - 30, 40, 8, LCDHEIGHT - 100, 0, val, 65535);
        
        // Clear button. Assigned tag = 206.
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.            
        DLTag(206);
        CMDButton(LCDWIDTH - 35, LCDHEIGHT - 45, 35, 25, 26, 0, "CLR");
        
        // Exit button. Assigned tag = 205.            
        DLTag(D5_EXIT);
        CMDButton(10, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");     
        // Disable tags.
        DLTagMask(0);
        
    FT_ListEnd(END_DL_SWAP);
   
}

/* [] END OF FILE */
