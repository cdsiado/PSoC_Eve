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
#include <stdlib.h>

#include "..\..\..\PSoC_Eve_Library\PsoCEve.h"
#include "..\PSoC_FatFs_Library\diskio.h"
#include "..\PSoC_FatFs_Library\ff.h"
#include "demo_3.h"

// storage for callback.
static void (*TouchCallback)(DEMO_3_EVENTS button) = 0;

/* *** Variables. *************************************************************
*/


/* *** Function prototypes. ***************************************************
*/
void Demo_3_Screen();
void Demo_3_Loop(); 

void PlayMusic();

/* *** Demo initialization. ***************************************************
*/
void* Demo_3_Start(void (*touchcallback)(DEMO_3_EVENTS button), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_3_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    closefunction = 0;        // This demo, doesn´t need a closing function.  
    return Demo_3_Loop;
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_3_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D3_BTN_EXIT) // exit button.
    {
        (*TouchCallback)(rdtag);
    }
}

/* *** Paint contents of screen. **********************************************
*/
void Demo_3_Screen()
{
    FATFS fatfs;
    FIL musicfile;
    uint8 resultf;
    uint32 filesize;
    
    uint8 rdbuffer[512];
    unsigned int bytesreaded;

    char tmpchar;
    uint8 filename = 1;
    char filenamestr[20];
    
    uint8 exit = 0;

    
    /* *** Show message while loading image. *** */
    FT_ListStart(DLIST);
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show message.
        DLColorRGB(0x00, 0xFF, 0x00);
        CMDText( LCDWIDTH / 2, 50, 29, OPT_CENTERX | OPT_CENTERX, "Loading... Please wait...");

    FT_ListEnd(END_DL_SWAP);
    
    // ************************************************************************
    
    /* Mount sdcard. */
    resultf = f_mount(&fatfs, "", 1);
    
    if (resultf != FR_OK)
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
            CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
            CMDText( 10, 50, 30, 0, "Screen: DEMO 3 ()");
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);
            
            // Show top message.
            DLColorRGB(0xFF, 0x00, 0x00);
            CMDText( 50, 150, 30, 0, "*** SDCard mount error...");
                        
            // Exit button..
            CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
            DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
            DLTag(D3_BTN_EXIT);             // For touch. Assign tag 1 to this button.
            CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
            
        /* Finish current display list. Make SWAP. */
        FT_ListEnd(END_DL_SWAP); 
        
        return;
    }
    
    // ************************************************************************
    
    FT_Audio_Unmute();
    
    FT_Register_Write(REG_PLAYBACK_FREQ, 44100);
    FT_Register_Write(REG_PLAYBACK_START, RAM_G);
    FT_Register_Write(REG_PLAYBACK_FORMAT, 1);
    FT_Register_Write(REG_VOL_PB, 255);
    FT_Register_Write(REG_PLAYBACK_LOOP, 0);
    
    while (filename < 10)
    {
        itoa(filename, filenamestr, 10);
        tmpchar = filenamestr[0];
        strcpy(filenamestr, "/audios/");
        filenamestr[8] = tmpchar;
        strcpy(filenamestr + 9, ".raw\0");
        
        /* Open sound file. */
        resultf = f_open(&musicfile, filenamestr, FA_READ);
        
        if (resultf != FR_OK)
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
            CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
            CMDText( 10, 50, 30, 0, "Screen: DEMO 3 ()");

            DLColorRGB(0xFF, 0x00, 0x00);
            CMDText( 50, 150, 30, 0, "*** File error...");
            
            /* Finish current display list. Make SWAP. */
            FT_ListEnd(END_DL_SWAP);
        }
        else
        {
            // Show number.
            FT_ListStart(DLIST);
                
            // Num. format for Vertex2F.
            DLVertexFormat(VERTEX_FORMAT_1);    // 1/1    
        
            // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);
            
            // Show top message.
            DLColorRGB(0xFF, 0x00, 0x00);
            CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
            CMDText( 10, 50, 30, 0, "Screen: DEMO 3 ()");

            DLColorRGB(0xFF, 0x00, 0x00);
            CMDNumber( 50, 150, 30, 0, filename);
            
            /* Finish current display list. Make SWAP. */
            FT_ListEnd(END_DL_SWAP);
            
            // *********** Copy file content to RAM_G offset 0.
            
            filesize = f_size(&musicfile);
            FT_Register_Write(REG_PLAYBACK_LENGTH, filesize);
            
            /* Copy file contents to RAM_G offset 0. */
            FT_Transfer_Start(RAM_G | MEMORY_WRITE);
            
            exit = 0;
            while(!exit)
            {
                f_read(&musicfile, rdbuffer, 512, &bytesreaded);
                FT_Send_ByteArray(rdbuffer, bytesreaded);
                
                filesize -= bytesreaded;
                
                if (filesize <= 0) exit = 1;
            }
            
            FT_Transfer_End();
            
            f_close(&musicfile);
            
            // Play sound.
            FT_Register_Write(REG_PLAYBACK_PLAY, 1);
            
            // Whait until finis.
            while(FT_Register_Read(REG_PLAYBACK_PLAY)) {};
            
        }

        filename++;
    }
    
    FT_Register_Write(REG_VOL_PB, 0);
    FT_Register_Write(REG_PLAYBACK_PLAY, 0);
    
    
    // Show error.
    FT_ListStart(DLIST);
        
    // Num. format for Vertex2F.
    DLVertexFormat(VERTEX_FORMAT_1);    // 1/1    

    // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    
    // Show top message.
    DLColorRGB(0xFF, 0x00, 0x00);
    CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
    CMDText( 10, 50, 30, 0, "Screen: DEMO 3 ()");
    
    DLColorRGB(0xFF, 0x00, 0x00);
    CMDText( 50, 150, 30, 0, "Finished...");
                
    // Exit button..
    CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
    DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
    DLTag(D3_BTN_EXIT);             // For touch. Assign tag 1 to this button.
    CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
    
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP);    
}


/* [] END OF FILE */
