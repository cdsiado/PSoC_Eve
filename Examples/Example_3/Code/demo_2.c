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
#include "..\PSoC_FatFs_Library\diskio.h"
#include "..\PSoC_FatFs_Library\ff.h"
#include "demo_2.h"

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
    FATFS fatfs;
    FIL imgfile;
    uint8 resultf;
    
    uint8 rdbuffer[512];
    unsigned int bytesreaded;
    
    uint8 exit = 0;
        
    uint8 sdcarderror = 0;      // 1 = can not mount, 2 = file not found.
    
#if defined EVE_FT800
    FT_ListStart(DLIST);

        // Num. format for Vertex2F.
        DLVertexFormat(VERTEX_FORMAT_1);    // 1/1    
    
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "This test only for FT81x");
        
        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D2_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP);   
    
    return;
#endif

    /* *** Show message while loading image. *** */
    FT_ListStart(DLIST);
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show message.
        DLColorRGB(0x00, 0xFF, 0x00);
        CMDText( LCDWIDTH / 2, 50, 29, OPT_CENTERX | OPT_CENTERX, "Loading... Please wait...");
        CMDText( LCDWIDTH / 2, 80, 29, OPT_CENTERX | OPT_CENTERX, "...be patient, it's a bit slow...");

    FT_ListEnd(END_DL_SWAP);
    
    // ************************************************************************
    
    /* Mount sdcard. */
    resultf = f_mount(&fatfs, "", 1);
    if (resultf != FR_OK)
    {
        sdcarderror = 1;
        return;
    }
    
    /* Open image file. */
    /* *** Images names are hardcoded here. *** */
    resultf = f_open(&imgfile, "/photos/h_ft810.bin", FA_READ);
    
    if (resultf != FR_OK)
    {
        sdcarderror = 2;
        f_mount(NULL, "", 1);                   // unmount sdcard.
        return;
    }
    
    if (sdcarderror != 0)
    {
        // Show error.
        FT_ListStart(DLIST);
                
            // Num. format for Vertex2F.
            DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);
            
            // Show top message.
            DLColorRGB(0xFF, 0x00, 0x00);
            if (sdcarderror == 1)
                CMDText( 10, 10, 30, 0, "*** SDCard mount error...");
            else if (sdcarderror == 1)
                CMDText( 10, 50, 30, 0, "*** File not found...");
                        
            // Exit button..
            CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
            DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
            DLTag(D2_BTN_EXIT);             // For touch. Assign tag 1 to this button.
            CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            
        /* Finish current display list. Make SWAP. */
        FT_ListEnd(END_DL_SWAP);               
    }
    else
    {
//        FT_ListStart(DLIST); 
//        CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory at offset 0.
//        FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
//        FT_ListEnd(END_DL_NOSWAP);        
        
        /* Load the image to RAM_G */
        FT_ListStart(DLIST);

            // Inflate data in RAM_G memory at offset 0.
            CMDInflate(RAM_G);                                      
            
            // Remember!!. Data after CMDInflate have to be four bytes aligned.
            // Will read data image in blocks of 512 bytes. 512 is multiple of 4.
            // Will use 'FT_Send_ByteArray' for blocks of 512 bytes.
            // Then, if last block < 512. It can be four byte aligned or not depending on length.
            // So last block will be sent using 'FT_Write_ByteArray_4'
            exit = 0;
            while (!exit)
            {
                f_read(&imgfile, rdbuffer, 512, &bytesreaded);
                
                if (bytesreaded < 512)              // it is the last block.
                {
                    FT_Write_ByteArray_4(rdbuffer, bytesreaded);
                    exit = 1;
                }
                else 
                {
                    FT_Send_ByteArray(rdbuffer, 512);
                }
            }
             
            // Close image file.
            f_close(&imgfile);
            
            // Num. format for Vertex2F.
            DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);             
        
            // Center image on screen.
            DLBegin(PRIMITIVE_BITMAP);
                DLBitmapSource(RAM_G);
                DLBitmapLayout(BITMAP_LAYOUT_RGB565, 800 * 2, 480);
                DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 800, 480); 
                DLVertex2F(0, 0);          
            
            // Exit button..
            DLTag(D2_BTN_EXIT);             // For touch. Assign tag 1 to this button.
            CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            
        FT_ListEnd(END_DL_SWAP);
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
 

}

/* [] END OF FILE */
