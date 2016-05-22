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
#include "demo_11.h"
#include "Demos_Resources.h"
#include "..\..\..\PSoC_Eve_Library\PSoCEve_Config.h"

// storage for callback.
static void (*TouchCallback)(DEMO_11_EVENTS button) = 0;

/* *** Variables. *************************************************************
*/

/* *** Function prototypes. ***************************************************
*/
void Demo_11_Screen();
void Demo_11_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_11_Start(void (*touchcallback)(DEMO_11_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_11_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_11_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_11_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D11_BTN_EXIT)
        (*TouchCallback)(rdtag);  
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_11_Screen()
{
    unsigned int bitmaplength;
    
    // Place the bitmap to be used in RAM_G at offset 0. Using zlib compressed version of bitmap.
    
    bitmaplength = sizeof(testbitmapzlib);
    
    FT_ListStart(DLIST); 
        CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory at offset 0.
        FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
    FT_ListEnd(END_DL_NOSWAP);
    
    // Will test CMD_MEMCPY command.
    // Copy bitmap from offset 0, to offset 10000.
    // Then, show the bitmap.

    FT_ListStart(DLIST);

        // Num. format for Vertex2F.
        DLVertexFormat(VERTEX_FORMAT_1);    // 1/1    
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 11 ()"); 
        DLColorRGB(0xFF, 0xFF, 0xFF);
        
        CMDMemCopy(10000, 0, 8192);
        
        DLBegin(PRIMITIVE_BITMAP);
            DLBitmapSource(10000);
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
            DLVertex2F(5, 100);
            
            // Issues with CMDMemWrite in FT_801.
            // Maintain this #if until solved.
#if defined EVE_FT810    
        // Now, will test CMD_MEMWRITE command.
        // Send uncompressed bitmap from flash to RAM_G offset 30000.
        CMDMemWrite(RAM_G + 30000, 8192);
        FT_Write_ByteArray_4(testbitmap, 8192);
        
        // Will test vertex_translate functions also.
        
        #if defined EVE_FT810
            DLVertexTranslateX(100 * 16);
            DLVertexTranslateY(100 * 16);
        #endif
        
        DLColorMask(0, 1, 1, 1);        // Mask red color. Testing COLOR_MASK command.
        DLBegin(PRIMITIVE_BITMAP);
            DLBitmapSource(30000);
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
            DLVertex2F(100, 100);
            
        #if defined EVE_FT810           // Restore.
            DLVertexTranslateX(0 * 16);
            DLVertexTranslateY(0 * 16);
        #endif            
        
        DLColorMask(1, 1, 1, 1);        // Restore.
#endif
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D11_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP); 
}

/* [] END OF FILE */
