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
#include "demo_8.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_8_EVENTS event) = 0;

/* *** Function prototypes. ***************************************************
*/

void Demo_8_Screen();
void Demo_8_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_8_Start(void (*touchcallback)(DEMO_8_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_8_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = 0;         
    return Demo_8_Loop;
}


/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_8_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D8_BTN_EXIT)
    {
        (*TouchCallback)(rdtag);
    }
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_8_Screen()
{
    unsigned int bitmaplength;
    uint16 wrregister;
    uint32 ptrend;
    
    // First, inflate int RAM_G at offset 0 the zlib compressed version of the bitmap.
    
    bitmaplength = sizeof(testbitmapzlib);
    
    FT_ListStart(DLIST); 
        CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory at offset 0.
        FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
    FT_ListEnd(END_DL_NOSWAP);
    
        // Now, we want to get the pointer rom RAM_g of the last inflated data.
    ptrend = CMDGetPtr();
    
        // Now, we send the uncompressed version of the bitmap next to previous bitmap.
    bitmaplength = sizeof(testbitmap);                  // Get size of the array.
 
    FT_Transfer_Start((RAM_G + ptrend) | MEMORY_WRITE);            // Start transfer of data to FTDI chip.
                                                        //    Will be stored at offset 0x00 in RAM_G
        FT_Send_ByteArray(testbitmap, bitmaplength); 
    FT_Transfer_End();                                  // End the transfer.
    
        // At this time, we know we have the compressed version of the bitmap in RAM_G at offset 0,
        // (i call it the compressed version, but realize it was uncompressed into RAM_G using
        //  inflate command),
        // and the uncompressed version at offset 'ptrend'.
    
    
    FT_ListStart(DLIST); 
        
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 8 (bitmaps)");
        
        DLColorRGB(0xFF, 0xFF, 0xFF);
        DLVertexFormat(VERTEX_FORMAT_1);
        
        /* **************
            CMDSetBitmap doesn´t work in FT810
            Once debuged and solved, this part will be changed.
        ************** */
        DLBegin(PRIMITIVE_BITMAP);          // Start new primitive (BITMAP.
            DLBitmapSource(0x00);           // Source address 0 in RAM_G.
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64);        
            DLVertex2F(100, 150);
            
        // Show the compressed version of the bitmap using command SetBitmap.
//        DLBegin(PRIMITIVE_BITMAP);
//            CMDSetBitmap(0, BITMAP_LAYOUT_RGB565, 64, 64);
//            DLVertex2F(100, 150);
        /* *************************** */
        
        // Show the uncompressed version of the bitmap the regular way.
        DLBegin(PRIMITIVE_BITMAP);          // Start new primitive (BITMAP.
            DLBitmapSource(ptrend);         // Source address 0 in RAM_G.
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64);        
            DLVertex2F(200, 150);
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D8_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
    FT_ListEnd(END_DL_SWAP);    
}

/* [] END OF FILE */
