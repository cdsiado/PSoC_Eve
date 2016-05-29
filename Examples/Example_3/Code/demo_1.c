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
#include "demo_1.h"


// storage for callback.
static void (*TouchCallback)(DEMO_1_EVENTS button) = 0;

/* *** Variables. *************************************************************
*/

uint8 jpgimage = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_1_Screen();
void Demo_1_Loop(); 

void LoadJPG_ToRAMG(uint8 image);

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
    switch (rdtag)
    {
        case D1_BTN_NEXT:
        {
            FT_Sound_Play(0x50, 0xc0);
            jpgimage++;
            if (jpgimage == 8) jpgimage = 0;
            LoadJPG_ToRAMG(jpgimage);
        }; break;
        
        case D1_BTN_EXIT:
        {
            (*TouchCallback)(rdtag);
        }; break;
    }
        
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_1_Screen()
{
    jpgimage = 0;
    LoadJPG_ToRAMG(jpgimage);
}

void LoadJPG_ToRAMG(uint8 image)
{
    FATFS fatfs;
    FIL imgfile;
    uint8 resultf;
    
    uint8 rdbuffer[512];
    unsigned int bytesreaded;

    uint32 filesize = 0;
        
    uint8 sdcarderror = 0;      // 1 = can not mount, 2 = file not found.

    /* *** Show message while loading image. *** */
    FT_ListStart(DLIST);
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show message.
        DLColorRGB(0x00, 0xFF, 0x00);
        CMDText( LCDWIDTH / 2, LCDHEIGHT / 2, 29, OPT_CENTERX | OPT_CENTERX, "Loading... Please wait...");

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
    switch (image)
    {
        case 0: resultf = f_open(&imgfile, "/photos/a.jpg", FA_READ); break;
        case 1: resultf = f_open(&imgfile, "/photos/b.jpg", FA_READ); break;
        case 2: resultf = f_open(&imgfile, "/photos/c.jpg", FA_READ); break;
        case 3: resultf = f_open(&imgfile, "/photos/d.jpg", FA_READ); break;
        case 4: resultf = f_open(&imgfile, "/photos/e.jpg", FA_READ); break;
        case 5: resultf = f_open(&imgfile, "/photos/f.jpg", FA_READ); break;
        case 6: resultf = f_open(&imgfile, "/photos/g.jpg", FA_READ); break;
        
        #if defined EVE_FT800
            case 7: resultf = f_open(&imgfile, "/photos/h_ft800.jpg", FA_READ); break;
        #endif
        
        #if defined EVE_FT810
            case 7: resultf = f_open(&imgfile, "/photos/h_ft810.jpg", FA_READ); break;
        #endif
    }
    
    if (resultf != FR_OK)
    {
        sdcarderror = 2;
        f_mount(NULL, "", 1);                   // unmount sdcard.
        return;
    }
    
    filesize = f_size(&imgfile);
    
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
            DLTag(D1_BTN_EXIT);             // For touch. Assign tag 1 to this button.
            CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            
        /* Finish current display list. Make SWAP. */
        FT_ListEnd(END_DL_SWAP);               
    }
    else
    {
        /* Load the image to RAM_G */
        FT_ListStart(DLIST);
            // Num. format for Vertex2F.
            DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1); 
            
            // Load image to RAM_G
            CMDLoadImage(RAM_G, OPT_RGB565 | OPT_NODL);        // RAM_G offset = 0. Convert to RGB565.
            
            // Remember!!. Data after CMDLoadImage have to be four bytes aligned.
            // Will read data image in blocks of 512 bytes. 512 is multiple of 4.
            // Will use 'FT_Send_ByteArray' for blocks of 512 bytes.
            // Then, if last block < 512. It can be four byte aligned or not depending on length.
            // So last block will be sent using 'FT_Write_ByteArray_4'

            while (filesize > 0)
            {
                f_read(&imgfile, rdbuffer, 512, &bytesreaded);
                
                if (bytesreaded < 512) FT_Write_ByteArray_4(rdbuffer, bytesreaded);
                else FT_Send_ByteArray(rdbuffer, 512);

                    
                filesize -= bytesreaded;
            }
             
            // Close image file.
            f_close(&imgfile);

            DLBegin(PRIMITIVE_BITMAP);
            DLBitmapSource(0);
            DLBitmapLayout(BITMAP_LAYOUT_RGB565, 375 * 2, 250);
            DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 375, 250);

                switch (image)
                {
                    case 0: 
                    case 2: DLVertex2F((int16)((LCDWIDTH - 375) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 1: DLVertex2F((int16)((LCDWIDTH - 374) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 3: DLVertex2F((int16)((LCDWIDTH - 376) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 4: DLVertex2F((int16)((LCDWIDTH - 166) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 5: DLVertex2F((int16)((LCDWIDTH - 361) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 6: DLVertex2F((int16)((LCDWIDTH - 333) / 2), (int16)((LCDHEIGHT - 250) /2)); break;
                    case 7: DLVertex2F(0, 0); break;
                }         

            
            // Next button..
            CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
            DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
            DLTag(D1_BTN_NEXT);             // For touch. Assign tag 1 to this button.
            CMDButton(20, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Next");
            
            // Exit button..
            DLTag(D1_BTN_EXIT);             // For touch. Assign tag 1 to this button.
            CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            
        FT_ListEnd(END_DL_SWAP);
    }
}

/* [] END OF FILE */
