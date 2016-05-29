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
#include "demo_3.h"

// storage for callback.
static void (*TouchCallback)(DEMO_3_EVENTS button) = 0;

/* *** Variables. *************************************************************
*/

    // stores state of button for touch demo.
uint8 button_1_state, button_1_previous_state = 0;
uint8 button_2_state, button_2_previous_state = 0;

/* *** Function prototypes. ***************************************************
*/
void Demo_3_Screen();
void Demo_3_Loop(); 

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
    switch(rdtag)
    {
        case 0:
        {
            button_1_state = button_2_state = 0;
        }; break;
        
        case D3_BTN_EXIT: // exit button.
        {
            (*TouchCallback)(rdtag); break;
        }; break;
            
        case 11: // demo button 1.
        {
            button_1_state = 1;
        }; break;
            
        case 12: // demo button 2.
        {
            button_2_state = 1;
        }; break;
    }
    
    if ((button_1_state != button_1_previous_state) || (button_2_state != button_2_previous_state))
    {
        Demo_3_Screen();
        button_1_previous_state = button_1_state;
        button_2_previous_state = button_2_state;
    }
}


/* *** Paint contents of screen. **********************************************
*/
void Demo_3_Screen()
{

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
        CMDText( 10, 50, 30, 0, "Screen: DEMO 3 ()"); 
    
        // Show some keys. They will do nothing, only for demo.
        CMDKeys(10, 100, 400, 50, 29, OPT_3D, "ABCDEFGHI");
        
        // Show two new buttons.
        // Will use 3D effect, for unpressed button. Flat effect for pressed button.
        DLTag(11);
        if (!button_1_state)
            CMDButton(10, 200, 200, 50, 29, OPT_3D, "Touch This");
        else 
            CMDButton(10, 200, 200, 50, 29, OPT_FLAT, "Touch This");
            
        DLTag(12);
        if (!button_2_state)
            CMDButton(250, 200, 200, 50, 29, OPT_3D, "or This");
        else
            CMDButton(250, 200, 200, 50, 29, OPT_FLAT, "or This");

        
        // Exit button..
        CMDFgcolor(0x00, 0x00, 0xFF);   // Button color = blue.
        DLColorRGB(0xFF, 0xFF, 0xFF);   // Text color = white.
        DLTag(D3_BTN_EXIT);             // For touch. Assign tag 1 to this button.
        CMDButton(LCDWIDTH - 120, LCDHEIGHT - 30, 100, 30, 28, OPT_3D, (char*)"Exit");
        
    /* Finish current display list. Make SWAP. */
    FT_ListEnd(END_DL_SWAP); 
}

/* [] END OF FILE */
