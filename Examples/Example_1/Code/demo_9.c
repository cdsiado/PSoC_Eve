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
#include "demo_9.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_9_EVENTS button) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_9_Screen();
void Demo_9_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_9_Start(void (*touchcallback)(DEMO_9_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_9_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_9_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_9_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D9_BTN_EXIT)
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_9_Screen()
{
    unsigned int bitmaplength;
    
    // Place the bitmap to be used in RAM_G. Using zlib compressed version of bitmap.
    
    bitmaplength = sizeof(testbitmapzlib);
    
    FT_ListStart(DLIST); 
        CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory at offset 0.
        FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
    FT_ListEnd(END_DL_NOSWAP);
  
    
    /* Start a new Display List. */
    FT_ListStart(DLIST);
    
        // Num. format for Vertex2F.
        DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
    
        // Clear screen. 
        // Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 9 (bitmaps)");
        DLColorRGB(0xFF, 0xFF, 0xFF);
        
        // Here we save context because the matrix transformations in next
        // tests will affect the text at the exit button.
        // At the end we restore context so text in exit button is shown correctly.
        DLSaveContext();
        
        // normal bitmap
        
        DLBegin(PRIMITIVE_BITMAP);        // Start new primitive (BITMAP.
            DLBitmapSource(0x00);         // Source address 0 in RAM_G.
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
            DLVertex2F(5, 100);
            
            // Double widht
            DLBitmapTransformA(128);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 128, 64);
            DLVertex2F(70, 100);
            
            DLRestoreContext();
            // Double height
            DLBitmapTransformE(128);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 128);
            DLVertex2F(5, 100 + 65);
            
        DLRestoreContext(); 
        
            // Scale
        DLBegin(PRIMITIVE_BITMAP);
            DLBitmapHandle(0);
            DLBitmapSource(0x00);         // Source address 0 in RAM_G.
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64);
            
            CMDLoadIdentity();
            CMDScale(2 * 65536, 2 * 65536);
            CMDSetmatrix();
            DLVertex2II(70, 100 + 65, 0, 0);
            
            // Rotate
            CMDLoadIdentity();
            CMDRotate(-32 * 65536 / 360);
            CMDSetmatrix();
            DLVertex2II(70 + 70, 100 + 65, 0, 0);
            
            // Scale & translate
            CMDLoadIdentity();
            CMDTranslate(65536 * 32, 65536 * 32);
            CMDScale(2 * 65536, 2 * 65536);
            CMDTranslate(65536 * -32, 65536 * -32);
            CMDSetmatrix();
            DLVertex2II(70 + 70 + 70, 100 + 65, 0, 0);


        // Restore the context.
        DLRestoreContext();
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D9_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP);        
}

/* [] END OF FILE */
