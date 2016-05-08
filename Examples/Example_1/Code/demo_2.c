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
#include "demo_2.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_2_EVENTS button) = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_2_Screen();
void Demo_2_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_2_Start(void (*touchcallback)(DEMO_2_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_2_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_2_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_2_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D2_BTN_EXIT)
        (*TouchCallback)(rdtag);
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_2_Screen()
{
    /* *** In this demo we will use a primitive bitmap.
           The bitmap is stored in Demos_Resources.h file as a const uint8 array.
           It is a 64x64 bitmap in RGB 565 format. Converted using FTDI tools.
           The first thing we will do, is to copy the contents of bitmap uint8 array to 
           RAM_G inside FTDI EVE chip. This way, bitmap data will be ready to be used by
           the following display list.
    */
    
    unsigned int bitmaplength = sizeof(testbitmap);     // Get size of the array.
 
    FT_Transfer_Start(RAM_G | MEMORY_WRITE);            // Start transfer of data to FTDI chip.
                                                        //    Will be stored at offset 0x00 in RAM_G
        FT_Send_ByteArray(testbitmap, bitmaplength); 
    FT_Transfer_End();                                  // End the transfer.

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
        CMDText( 10, 50, 30, 0, "Screen: DEMO 2 (primitives)");
        
        DLBegin(PRIMITIVE_EDGE_STRIP_L);    // *** Edge Strip Left.
            DLColorRGB(0xFF, 0x00, 0x00);       // Red color.
            DLVertex2F(50, 100);
            DLVertex2F(100, 150);
        DLBegin(PRIMITIVE_EDGE_STRIP_R);    // *** Edge Strip Right.
            DLColorRGB(0x00, 0xFF, 0x00);       // Green color.
            DLVertex2F((LCDWIDTH - 50), 250);
            DLVertex2F((LCDWIDTH - 100), 270);
        DLBegin(PRIMITIVE_EDGE_STRIP_B);    // *** Edge Strip Bottom.
            DLColorRGB(0x00, 0x00, 0xFF);       // Blue color.
            DLVertex2F(50, (LCDHEIGHT - 20));
            DLVertex2F(150, (LCDHEIGHT - 50));
            DLVertex2F(250, (LCDHEIGHT - 30));
        DLScissorXY(0, 99);                 // *** Here, we use scissor command to protect the text.
        DLScissorSize(LCDWIDTH, LCDHEIGHT); //  to be overwritten with the next edge primitive.                                           
        DLBegin(PRIMITIVE_EDGE_STRIP_A);    // *** Edge Strip Top.
            DLColorRGB(0xFF, 0xFF, 0xFF);       // White color.
            DLVertex2F(100, 100);
            DLVertex2F(200, 150); 
            DLVertex2F(250, 200);
            DLVertex2F(350, 100);
            
        DLBegin(PRIMITIVE_BITMAP);          // *** The bitmap.
            DLColorRGB(0xFF, 0xFF, 0xFF);       // Set color to black or the bitmap will be colored
                                                //    with the previously used color.
            DLBitmapSource(0x00);               // Source is offset 0x00 in RAM_G.
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
            DLVertex2F(200, 220);
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D2_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120 - 20, LCDHEIGHT - 50 - 20, 120, 50, 30, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP); 
}

/* [] END OF FILE */
