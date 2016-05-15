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
#include "demo_7.h"
#include "Demos_Resources.h"

// storage for callback.
static void (*TouchCallback)(DEMO_7_EVENTS event) = 0;

/* *** Function prototypes. ***************************************************
*/

void Demo_7_Screen();
void Demo_7_Loop(); 

/* *** Demo initialization. ***************************************************
*/
void* Demo_7_Start(void (*touchcallback)(DEMO_7_EVENTS event), void (**closefunction)())
{
    /* Paint screen contents. */
    Demo_7_Screen();
    
    /* Store callback pointer. */
    TouchCallback = touchcallback;
    
    /* Return address of this demo main loop function. Also for closing function. */
    *closefunction = 0;         
    return Demo_7_Loop;
}


/* *** Demo main loop. To be called from the program main loop. ***************
*/
void Demo_7_Loop()
{
    // Here we read the TAG register from EVE chip to know if a button is pressed.
    uint8 rdtag = FT_Read_Byte(REG_TOUCH_TAG);
    
    // Call the callback function with value of TAG.
    if (rdtag == D7_BTN_EXIT)
    {
        (*TouchCallback)(rdtag);
    }
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_7_Screen()
{
    
    FT_ListStart(DLIST); 
        
        // Clear screen. Clear Stencil buffer. Clear TAG buffer. 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        // Show top message.
        DLColorRGB(0xFF, 0x00, 0x00);
        CMDText( 10, 10, 30, 0, "PSoC Eve Library DEMO/TEST");
        CMDText( 10, 50, 30, 0, "Screen: DEMO 7 ()");
        
        // Gradient
        DLScissorXY(20, 100);
        DLScissorSize(LCDWIDTH - 40, 50);
        CMDGradient(20, 150, 0x00, 0x00, 0xFF, LCDWIDTH - 20, 150, 0xFF, 0x00, 0x00);
        DLScissorXY(0, 0);
        DLScissorSize(SCISSOR_RESTORE_SIZE, SCISSOR_RESTORE_SIZE);
        
        // Dial
        CMDFgcolor(0x00, 0x00, 0xFF);
        DLColorRGB(0xFF, 0xFF, 0xFF);
        CMDDial(70, 220, 40, 0, 0x8000);
                
        // Num. format for Vertex2F.
        DLVertexFormat(VERTEX_FORMAT_1);    // 1/1
        
        DLColorRGB(0x00, 0x00, 0xFF);
        DLBegin(PRIMITIVE_RECTANGLE);
            DLVertex2F(120, 170);
            DLVertex2F(LCDWIDTH - 20, 270);
            
        DLColorRGB(0xFF, 0xFF, 0xFF);
        // Color alpha
        CMDText(130, 170, 28, 0, "hackingchips");    // alpha default = 255; blend_func = default = transparent
        DLColorA(128);
        CMDText(130, 200, 28, 0, "hackingchips");
        DLColorA(64);
        CMDText(130, 230, 28, 0, "hackingchips");
        
        DLBlendFunc(BLEND_FUNC_SRC_ALPHA, BLEND_FUNC_ZERO);
        CMDText(270, 170, 28, 0, "hackingchips");    // alpha default = 255; blend_func = default = transparent
        DLColorA(128);
        CMDText(270, 200, 28, 0, "hackingchips");
        DLColorA(64);
        CMDText(270, 230, 28, 0, "hackingchips");
        
        // restore alpha, restore blend or it will affect button text.
        DLColorA(255);
        DLBlendFunc(BLEND_FUNC_SRC_ALPHA, BLEND_FUNC_ONE_MINUS_SRC_ALPHA);
        
        // testing button gradient. It will affect exit button.
        CMDFgcolor(0x10, 0x10, 0x10);
        CMDGradcolor(0xFF, 0x00, 0x00);
        
        
        // Exit button..
        //CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D7_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
        // Restore button gradient to default.
        CMDGradcolor(0xFF, 0xFF, 0xFF);
        
    FT_ListEnd(END_DL_SWAP);    
}

/* [] END OF FILE */
