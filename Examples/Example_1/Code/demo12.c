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
#include "demo_12.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_12_EVENTS event) = 0;

/* *** Variables. *************************************************************
*/

uint32 delay_a_counter = 500;
uint32 delay_b_counter = 16000;
uint32 talpha = 255;
uint32 tcolor = 1;

/* *** Function prototypes. ***************************************************
*/

void Demo_12_Screen();
void Demo_12_Loop(); 
void Demo_12_Stop();

/* *** Demo initialization. ***************************************************
*/
void* Demo_12_Start(void (*touchcallback)(DEMO_12_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_12_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = Demo_12_Stop;         
    return Demo_12_Loop;
}

/* *** Demo stop. **************************************************************
*/
void Demo_12_Stop()
{
    // Restore colors.
    FT_ListStart(DLIST);
        DLColorA(255);
        DLColorRGB(0xFF, 0xFF, 0xFF);
    FT_ListEnd(END_DL_SWAP);
}

/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_12_Loop()
{
    // Manage delays counters.
    
    if (delay_a_counter > 0) delay_a_counter--;             // Manage alpha.
    else
    {
        if (talpha > 0) talpha -= 5;
        else talpha = 255;
        
        FT_Register_Write(REG_MACRO_0, _DLColorA(talpha));
        
        delay_a_counter = 500;
    }
    
    if (delay_b_counter > 0) delay_b_counter--;             // Manage color.
    else
    {
        tcolor++;
        if (tcolor == 4) tcolor = 1;
        
        if (tcolor == 1) FT_Register_Write(REG_MACRO_1, _DLColorRGB(0xFF, 0x00, 0x00));
        else if (tcolor == 2) FT_Register_Write(REG_MACRO_1, _DLColorRGB(0x00, 0xFF, 0x00));
        else if (tcolor == 3) FT_Register_Write(REG_MACRO_1, _DLColorRGB(0x00, 0x00, 0xFF));
        
        delay_b_counter = 16000;
    }
    
    
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D12_EXIT)
        (*TouchCallback)(rdtag);  
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_12_Screen()
{
    uint32 ramdloffset;
    
    // In this demo, will use append command to add exit button to the display list.
    // First, create a display list only with the content for the exit button.
    // In FT_ListEnd, us END_NOSWAP, so the button is not displayed
    
    FT_ListStart(DLIST);
        // Exit button..
        DLColorA(255);
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D12_EXIT);                 // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
    FT_ListEnd(END_DL_NOSWAP);

    // At this moment, commands for the exit button are in display list ram, but
    // FT chips doesn´t show the result.
    
    // Now, we read proper register to know where is the pointer to the RAM_DL.
    // This way, we know the length of the data for the exit button.
    ramdloffset = FT_Register_Read(REG_CMD_DL);
    
    // Then, we copy the data for the button from RAM_DL to RAM_G, at offset 0.
    FT_ListStart(DLIST);
        CMDMemCopy(RAM_G, RAM_DL, ramdloffset);
    FT_ListEnd(END_DL_NOSWAP);
    // At this moment, data for the button is in RAM_G.
    
    // This demo will show also a text.
    // This text will change color and transparency every some time.
    // ¡¡¡ Realize !!! This is a demo/test. We are not using systick or some other
    // high precision counter/timer here. ok?
    // Counter speed will depend on PSoC frequency selected.
    
    // Assign the alpha command to macro 0.
    // Assign the color command to macro 1.
    FT_Register_Write(REG_MACRO_0, _DLColorA(talpha));
    FT_Register_Write(REG_MACRO_1, _DLColorRGB(0xFF, 0x00, 0x00));
    
    // Here is the display list.
    FT_ListStart(DLIST); 
        
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 12 (append & macro)"); 
        DLColorRGB(0xFF, 0xFF, 0xFF);   
        
        // Text
        DLMacro(0);
        DLMacro(1);
        CMDText(50, 150, 30, 0, "hackingchips.com");
        
        
        
        // Here, we use append command to place the data related to the 
        // usual exit button stored in RAM_G.
        CMDAppend(RAM_G, ramdloffset);
        
    FT_ListEnd(END_DL_SWAP);    
}

/* [] END OF FILE */
