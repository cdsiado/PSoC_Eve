/*******************************************************************************
* File Name: Test.c  
* Version 0.1 Alpha
*
* Description:
*  This file belongs to the PSoCEve library project.
*  Used for testing features of PSocEve library during development.
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#include <project.h>
#include "Test.h"
#include "..\..\PSocEveLibrary\PSoCEve.h"    
#include "Demos_Resources.h"


/*******************************************************************************
********************************************************************************
********************************************************************************
*   Test.
*******************************************************************************
********************************************************************************
*******************************************************************************/

void T_Init()
{
    FT_Display_ON();
    FT_Register_Write(REG_PWM_DUTY, 128);
}

/*******************************************************************************
********************************************************************************
********************************************************************************
*   Test. Related to DISPLAY LIST commands.
*******************************************************************************
********************************************************************************
*******************************************************************************/

void T_DL_A()
{
    T_CMD_COLDSTART();
    // Test: CLEAR_COLOR_RGB, CLEAR
    
    FT_ListStart(DISPLAY);                              // Start the display list.
    DLClearColorRGB(0xFF, 0x00, 0x00);                  // Set red color for background. 
    DLClear(1, 1, 1);                                   // Clear all (color, stencil and tag buffer).
    FT_ListEnd(END_DL_NOSWAP);                          // End the display list.
    CyDelay(1000);                              

    FT_ListStart(DISPLAY);                             // Start the display list.
    DLClearColorRGB(0x00, 0xFF, 0x00);                  // Set red color for background. 
    DLClear(1, 1, 1);                  // Clear all (color, stencil and tag buffer).
    FT_ListEnd(END_DL_NOSWAP);                                     // End the display list.
    CyDelay(1000); 

    FT_ListStart(DISPLAY);                             // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0xFF); // Set red color for background. 
    DLClear(1, 1, 1);                  // Clear all (color, stencil and tag buffer).
    FT_ListEnd(END_DL_NOSWAP);   
    CyDelay(1000); 

    FT_ListStart(DISPLAY);             // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00); // Set red color for background. 
    DLClear(1, 1, 1);                  // Clear all (color, stencil and tag buffer).
    FT_ListEnd(END_DL_NOSWAP); 
}

void T_DL_PRIMITIVE_POINT()
{
    T_CMD_COLDSTART();
    // Test also: DL_COLOR_RGB, DL_VERTEXII, DL_POINT_SIZE, DL_END,
    //     DL_LINE_WIDTH
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    DLColorRGB(0xFF, 0xFF, 0xFF);        // White color.
    DLBegin(PRIMITIVE_POINT);            // Begin a primitive (POINT)
    DLVertex2II(10, 10, 0, 0);           // First point.
    DLPointSize(50);                     // Increase point size.
    DLVertex2II(240, 136, 0, 0);         // Second point.
    FT_ListEnd(END_DL_NOSWAP);
}

void T_DL_PRIMITIVE_LINE()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
       
    // Test PRIMITIVE_LINE
    DLColorRGB(0xFF, 0x00, 0x00);         // Red color.       
    DLBegin(PRIMITIVE_LINE);              // Begin a primitive (LINE)
        DLVertex2II(10, 10, 0, 0);        // First point (line from...)
        DLVertex2II(100, 10, 0, 0);       // Second point (to...)
        DLColorRGB(0x00, 0xFF, 0x00);
    DLBegin(PRIMITIVE_LINE);
        DLLineWidth(3);
        DLVertex2II(10, 30, 0, 0);        // First point (line from...)
        DLVertex2II(100, 100, 0, 0);      // Second point (to...)
        DLEnd();
        DLColorRGB(0x00, 0x00, 0xFF);
        DLLineWidth(1);
    DLBegin(PRIMITIVE_LINE_STRIP);        // Begin a primitive (LINE_STRIP)
        DLVertex2II(200, 100, 0, 0);          
        DLVertex2II(300, 100, 0, 0);           
        DLVertex2II(300, 200, 0, 0);           
        DLVertex2II(200, 200, 0, 0);
        DLVertex2II(200, 100, 0, 0);
    FT_ListEnd(END_DL_NOSWAP);
}

void T_PRIMITIVE_EDGESTRIP()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).

    DLColorRGB(0xFF, 0xFF, 0xFF);
    DLLineWidth(1);
    DLBegin(PRIMITIVE_EDGE_STRIP_A);      // Begin a primitive (EDGE_STRIP_A)
        DLVertex2II(50, 50, 0, 0);        // First point (line from...)
        DLVertex2II(200, 70, 0, 0);       // Second point (to...)   

        DLColorRGB(0x00, 0xFF, 0x00);
    DLBegin(PRIMITIVE_EDGE_STRIP_L);      
        DLVertex2II(50, 70, 0, 0);           
        DLVertex2II(100, 90, 0, 0); 
        DLVertex2II(50, 100, 0, 0);
        DLVertex2II(75, 200, 0, 0);
    
    DLBegin(PRIMITIVE_EDGE_STRIP_R);      
        DLVertex2II(400, 70, 0, 0);           
        DLVertex2II(350, 100, 0, 0); 
        DLVertex2II(400, 200, 0, 0);
 
        DLColorRGB(0x00, 0x00, 0xFF);         
    DLBegin(PRIMITIVE_EDGE_STRIP_B);      
        DLVertex2II(200, 200, 0, 0);           
        DLVertex2II(350, 150, 0, 0); 
    FT_ListEnd(END_DL_NOSWAP);
}

void T_PRIMITIVE_RECTANGLE()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
        DLColorRGB(0x00, 0xFF, 0x00);         
        DLLineWidth(1);
    DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(40, 40, 0, 0);            
        DLVertex2II(100, 100, 0, 0);    
        DLColorRGB(0xFF, 0xFF, 0x00);         
        DLLineWidth(5);                  // Round rectangle
        DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(200, 200, 0, 0);            
        DLVertex2II(300, 250, 0, 0);
    FT_ListEnd(END_DL_NOSWAP);
}

void T_PRIMITIVE_BITMAP()
{
    unsigned int bitmaplength;
    
    T_CMD_COLDSTART();
    
    // Firt, copy the bitmap data from program memory to RAM_G (graphics RAM) of the 
    // EVE chip. Starting at address 0.
    bitmaplength = sizeof(testbitmap);
    FT_Transfer_Start(RAM_G | MEMORY_WRITE);
    FT_Send_ByteArray(testbitmap, bitmaplength);
    FT_Transfer_End();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    
    DLBegin(PRIMITIVE_BITMAP);            // Start new primitive (BITMAP.
        DLBitmapSource(0x00);             // Source address 0 in RAM_G.
        DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
        DLVertex2II(10, 10, 0, 0);        // Place the bitmap at 10, 10.
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 32, 32); 
        DLVertex2II(100, 10, 0, 0);       // Place, only a piece of the bitmap.
    FT_ListEnd(END_DL_NOSWAP);
    
    CyDelay(3000);
    
    // **********************************************************************    TODO: REvisar.
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    
    DLBegin(PRIMITIVE_BITMAP);            // Start new primitive (BITMAP.
        DLBitmapSource(0x00);             // Source address 0 in RAM_G.
        DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_REPEAT, BITMAP_SIZE_WRAP_REPEAT, 480, 272); 
        DLVertex2II(0, 0, 0, 0);          // Place the bitmap at 0, 0.
                                                        // Fill display.
    FT_ListEnd(END_DL_NOSWAP);
    
    CyDelay(3000);
    
    // **********************************************************************    
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    
    DLBegin(PRIMITIVE_BITMAP);           // Start new primitive (BITMAP.
        DLBitmapSource(0x00);            // Source address 0 in RAM_G.
        DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
        DLBitmapTransformA(120);
        DLBitmapTransformE(120);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 120, 120); 
        DLVertex2II(0, 0, 0, 0);         // Place the bitmap at 0, 0.
                                                        // Fill display.
    FT_ListEnd(END_DL_NOSWAP);
    
    CyDelay(3000);
    
    // **********************************************************************    
            
        // The same with bilinear filter.
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    
    DLBegin(PRIMITIVE_BITMAP);           // Start new primitive (BITMAP.
        DLBitmapSource(0x00);            // Source address 0 in RAM_G.
        DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
        DLBitmapTransformA(160);
        DLBitmapTransformE(160);
        DLBitmapSize(BITMAP_SIZE_FILTER_BILINEAR, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 240, 240); 
        DLVertex2II(0, 0, 0, 0);         // Place the bitmap at 0, 0.
                                         // Fill display.
    FT_ListEnd(END_DL_NOSWAP);
}

void T_DL_B() // Test DL_COLOR_A, DL_BLEND_FUNC
{
    T_CMD_COLDSTART();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
        DLColorRGB(0xFF, 0x00, 0x00);         
        DLLineWidth(1);
    DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(20, 100, 0, 0);            
        DLVertex2II(470, 150, 0, 0);   
        DLColorRGB(0xFF, 0xFF, 0xFF);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(40, 100, 31, 0x47); 
        DLColorA(128);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(80, 100, 31, 0x47); 
        DLColorA(64);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(120, 100, 31, 0x47);    
        DLColorA(255);
    FT_ListEnd(END_DL_NOSWAP);    
    
    CyDelay(3000);
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   // Set red color for background. 
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
        DLColorRGB(0xFF, 0x00, 0x00);         
        DLLineWidth(1);
    DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(20, 100, 0, 0);            
        DLVertex2II(470, 150, 0, 0);   
        DLColorRGB(0xFF, 0xFF, 0xFF);
        DLColorA(128);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(40, 100, 31, 0x47); 
        DLBlendFunc(BLEND_FUNC_SRC_ALPHA, BLEND_FUNC_ZERO);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(80, 100, 31, 0x47);
        DLBlendFunc(BLEND_FUNC_ZERO, BLEND_FUNC_SRC_ALPHA);
    DLBegin(PRIMITIVE_BITMAP);         
        DLVertex2II(120, 100, 31, 0x47);    
        DLColorA(255);
    FT_ListEnd(END_DL_NOSWAP);
}

void T_DL_SCISSOR()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(DISPLAY);               // Start the display list.
    DLClearColorRGB(0x00, 0x00, 0x00);   
    DLClear(1, 1, 1);                    // Clear all (color, stencil and tag buffer).
    DLScissorXY(40, 30);         
    DLScissorSize(80, 60);
    DLClearColorRGB(0x00, 0x00, 0xFF);   
    DLClear(1, 1, 1);      
    DLBegin(PRIMITIVE_BITMAP);         
    DLVertex2II(35, 20, 31, 0x47);
    FT_ListEnd(END_DL_NOSWAP);    
}

void T_DL_TAG_AND_MASK()
{
    uint32 firstrectanglecolor = 0x00FF00FF;
    uint32 secondrectanglecolor = 0xFF00FF00;
    
    uint8 exit = 0;
    
    uint8 readedtag = 0;
    
    T_CMD_COLDSTART();
    
    // Draw tree rectangles. 
    // First will have tag = 1. Second, tag = 2; Third, no tag.
    // Draw a button for exit, tag = 3.
    
    while (!exit)   // TODO: revisar, no funciona antes de calibrate, mal cambio colores.
    {
        FT_ListStart(COPROCESSOR); 
        DLClearColorRGB(0x00, 0x00, 0x00);
        DLClear(1, 1, 1);
        
        DLTagMask(1);
        
        DLTag(1);
        DLColorRGB((uint8)(firstrectanglecolor >> 16), (uint8)(firstrectanglecolor >> 8), (uint8)(firstrectanglecolor));
        DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(50, 50, 0, 0);            
        DLVertex2II(100, 100, 0, 0);    

        DLTag(2);
        DLColorRGB((uint8)(secondrectanglecolor >> 16), (uint8)(secondrectanglecolor >> 8), (uint8)(secondrectanglecolor));
        DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(150, 50, 0, 0);            
        DLVertex2II(200, 100, 0, 0);   
        
        DLTagMask(0);
        DLColorRGB(0xFF, 0xFF, 0xFF);
        DLBegin(PRIMITIVE_RECTANGLE);         
        DLVertex2II(250, 50, 0, 0);            
        DLVertex2II(300, 100, 0, 0);      
        
        DLTagMask(1);
        
        DLTag(3);
        CMDFgcolor(0xFF, 0xFF, 0x00);
        CMDButton(50, 200, 100, 50, 28, OPT_3D, (char*)"EXIT");
        FT_ListEnd(END_DL_SWAP);
        
        while (readedtag == 0)
        {
            readedtag = FT_Read_Byte(REG_TOUCH_TAG);
            
            if (readedtag == 1) 
            {
                firstrectanglecolor = ~firstrectanglecolor;
            }
            else if (readedtag == 2) 
            {
                secondrectanglecolor = ~secondrectanglecolor;
            }
            else if (readedtag == 3) exit = 1;
            
            readedtag = readedtag;
        }
                    
        readedtag = 0;
    }
}


/*******************************************************************************
********************************************************************************
********************************************************************************
*   Test. Related to COPROCESSOR commands.
*******************************************************************************
********************************************************************************
*******************************************************************************/

void T_CMD_GRADIENT()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);    
    CMDGradient(0, 0, 0, 0, 0xFF, 160, 0, 0xFF, 0x0, 0x0);
    FT_ListEnd(END_DL_SWAP);     
}

void T_CMD_TEXT()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR);
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    DLColorRGB(0xFF, 0x00, 0xFF);
    CMDText( 10, 10, 30, 0, "!Hello");
    DLColorRGB(0x00, 0x00, 0xFF);
    CMDText( 150, 150, 30, 0, "JESUSS25");
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_BUTTON()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDFgcolor(0xFF, 0xFF, 0x00);
    CMDButton(20, 20, 100, 50, 28, OPT_3D, (char*)"3d");
    CMDGradcolor(0xFF, 0x00, 0x00); // TODO: verificar.
    CMDButton(50, 150, 100, 50, 28, OPT_FLAT, (char*)"flat");
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_KEYS()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);    
    CMDFgcolor(0xFF, 0xFF, 0x00);
    CMDKeys(20, 20, 100, 50, 28, OPT_3D, (char*)"3d");
    CMDKeys(50, 150, 100, 50, 28, OPT_FLAT, (char*)"flat");
    FT_ListEnd(END_DL_SWAP);  
}

void T_CMD_PROGRESS()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR);
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDBgcolor(0xFF, 0x00, 0x00);
    CMDProgressBar(10, 10, 150, 20, OPT_3D, 50, 100); // TODO: Coordenadas?
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_SLIDER()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDFgcolor(0x00, 0xFF, 0x00);
    CMDBgcolor(0xFF, 0x00, 0x00);
    CMDSlider(10, 10, 150, 20, OPT_3D, 50, 100);
    CMDSlider(10, 100, 200, 20, OPT_FLAT, 50, 200);  
    CMDSlider(250, 10, 20, 150, OPT_3D, 50, 100);
    CMDSlider(300, 10, 20, 200, OPT_FLAT, 50, 200);
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_SCROLLBAR()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDFgcolor(0xFF, 0x00, 0x00);
    CMDBgcolor(0x00, 0xFF, 0x00); // <<<<< REVISAR
    CMDScrollBar(10, 10, 150, 20, OPT_3D, 10, 40, 100);
    CMDScrollBar(10, 100, 200, 20, OPT_FLAT, 10, 40, 100);  
    CMDScrollBar(250, 10, 20, 150, OPT_3D, 10, 40, 200);
    CMDScrollBar(300, 10, 20, 200, OPT_FLAT, 10, 40, 200);
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_TOGGLE()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);    
    CMDFgcolor(0xFF, 0xFF, 0x00);
    CMDBgcolor(0x00, 0x00, 0xFF);
    CMDToggle(50, 50, 200, 28, 0, TOGGLE_STATE_ON, (char*)"ON\xffOFF");
    CMDToggle(100, 100, 200, 28, 0, TOGGLE_STATE_OFF, (char*)"ON\xffOFF");
    FT_ListEnd(END_DL_SWAP);    
}

void T_CMD_GAUGE()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDBgcolor(0x00, 0x00, 0xFF);
    CMDGauge(70, 70, 50, OPT_3D, 5, 4, 30, 100);
    CMDGauge(180, 70, 50, OPT_FLAT, 5, 4, 30, 100); 
    CMDGauge(290, 70, 50, OPT_3D, 10, 2, 30, 100);
    CMDGauge(400, 70, 50, OPT_3D, 10, 1, 30, 100);
    CMDGauge(70, 180, 50, OPT_3D, 1, 10, 30, 100);
    CMDBgcolor(0x40, 0x20, 0x00);
    CMDGauge(180, 180, 50, OPT_3D, 5, 4, 30, 100);
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_CLOCK()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDBgcolor(0x00, 0x00, 0xFF); // <<<<< REVISAR
    CMDClock(70, 70, 50, OPT_3D, 15, 30, 42, 100);
    CMDClock(180, 70, 50, OPT_FLAT, 2, 45, 53, 100);
    FT_ListEnd(END_DL_SWAP); 
}

void T_CMD_CALIBRATE()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDCalibrate();
    FT_ListEnd(END_DL_SWAP);  
    
    while (!FTIsCoproccesorReady()) {}
}

void T_CMD_SPINNER()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    DLColorRGB(0x55, 0xFF, 0x55);
    CMDSpinner(240, 136, SPINNER_ROUND, 0);
    FT_ListEnd(END_DL_NOSWAP);
    
    CyDelay(5000);
    
    FT_ListStart(COPROCESSOR);
    CMDStop();
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_DIAL()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDFgcolor(0xFF, 0xFF, 0x00);
    CMDDial(70, 70, 50, OPT_3D, 30000);
    CMDDial(180, 70, 50, OPT_FLAT, 40000);
    FT_ListEnd(END_DL_SWAP); 
}

void T_CMD_NUMBER()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR);
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    DLColorRGB(0xFF, 0x00, 0x00);
    CMDNumber(10, 10, 28, 0, 100);
    DLColorRGB(0x00, 0xFF, 0x00);
    CMDNumber(40, 40, 30, OPT_SIGNED, -100);
    DLColorRGB(0x00, 0x00, 0xFF);
    CMDNumber(80, 80,30,0, 200);
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_SKETCH()
{
    T_CMD_COLDSTART();
    
    // Draw rectangle.
//    FT_ListStart(DISPLAY);                                      // Start the display list.
//    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
//    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
//    DLListNewItem(DLColorRGB(0x00, 0xFF, 0x00));         // Red color.       
//        DLListNewItem(DLLineWidth(1));
//    DLListNewItem(DLBegin(PRIMITIVE_LINE_STRIP));        // Begin a primitive (LINE_STRIP)
//        DLListNewItem(DLVertex2II(20, 20, 0, 0));          
//        DLListNewItem(DLVertex2II(300, 20, 0, 0));           
//        DLListNewItem(DLVertex2II(300, 250, 0, 0));           
//        DLListNewItem(DLVertex2II(20, 250, 0, 0));
//        DLListNewItem(DLVertex2II(20, 20, 0, 0));
//    FT_ListEnd(END_DL_NOSWAP);
    
    // Skecth
    FT_ListStart(COPROCESSOR);
    
    DLClearColorRGB(0x00, 0x00, 0x00);     // Set red color for background. 
    DLClear(1, 1, 1);                      // Clear all (color, stencil and tag buffer).
    DLColorRGB(0x00, 0xFF, 0x00);          // Red color. 
    
        DLLineWidth(1);                    // Draw green rectangle as sketching area.
    DLBegin(PRIMITIVE_LINE_STRIP);        
        DLVertex2II(20, 20, 0, 0);          
        DLVertex2II(300, 20, 0, 0);           
        DLVertex2II(300, 250, 0, 0);           
        DLVertex2II(20, 250, 0, 0);
        DLVertex2II(20, 20, 0, 0);
        
    DLTag(1);                              // Place "exit" button with tag=1 for touches.
    CMDButton(350, 50, 100, 50, 28, OPT_3D, (char*)"Exit");
    DLTagMask(0);
    
    DLColorRGB(0xFF, 0xFF, 0xFF);
    CMDMemZero(0, (LCDWIDTH * LCDHEIGHT / 8));          // Fill with zeroes area used to store the sketch
    CMDSketch(21, 21, 299, 249, 0, BITMAP_LAYOUT_L1);   // Start sketch
    FT_ListEnd(END_DL_SWAP);
    
    CyDelay(20000); // 20 seconds to draw
    
    FT_ListStart(COPROCESSOR);
    CMDStop();
    FT_ListEnd(END_DL_SWAP);
}

void T_CMD_LOGO()
{
    T_CMD_COLDSTART();
    
    FT_ListStart(COPROCESSOR); 
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    CMDLogo();
    FT_ListEnd(END_DL_SWAP);  
    
    while (!FTIsCoproccesorReady()) {}
}

void T_CMD_SCREENSAVER()
{
    unsigned int bitmaplength;
    
    T_CMD_COLDSTART();
    
    // Firt, copy the bitmap data from program memory to RAM_G (graphics RAM) of the 
    // EVE chip. Starting at address 0.
    bitmaplength = sizeof(testbitmap);
    FT_Transfer_Start(RAM_G | MEMORY_WRITE);
    FT_Write_ByteArray_4(testbitmap, bitmaplength);
    FT_Transfer_End();
        
    FT_ListStart(COPROCESSOR); 
    CMDScreenSaver();
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    DLBegin(PRIMITIVE_BITMAP);        // Start new primitive (BITMAP.
    DLBitmapSource(0x00);             // Source address 0 in RAM_G.
    DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
    DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
    DLMacro(0);
    FT_ListEnd(END_DL_SWAP);    
    
    CyDelay(10000); // Wait 10 seconds, then stop screensaver.
    
    FT_ListStart(COPROCESSOR);
    CMDStop();
    FT_ListEnd(END_DL_SWAP);    
}

void T_CMD_COLDSTART()
{
    FT_ListStart(COPROCESSOR);
    CMDColdstart();
    FT_ListEnd(END_DL_SWAP); 
    
    CyDelay(5);
}

void T_CMD_INFLATE()
{
    unsigned int bitmaplength;
    
    T_CMD_COLDSTART();    
    
    bitmaplength = sizeof(testbitmapzlib);
    
    FT_ListStart(COPROCESSOR); 
    CMDInflate(RAM_G);                                      // Inflate data in RAM_G memory.
    FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);     // Send Zlib data. 
    
    DLClearColorRGB(0x00, 0x00, 0x00);
    DLClear(1, 1, 1);
    DLBegin(PRIMITIVE_BITMAP);                              // Start new primitive (BITMAP.
    DLBitmapSource(0x00);                                   // Source address 0 in RAM_G.
    DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64);
    DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64); 
    DLVertex2F(100, 100);
    FT_ListEnd(END_DL_SWAP);     
}

/*******************************************************************************
********************************************************************************
********************************************************************************
*   Test. Related to sound.
*******************************************************************************
********************************************************************************
*******************************************************************************/

void T_SOUND()
{
    FT_Audio_Unmute();
    
    FT_Sound_Volume(0x80);      // Medium volume.
    FT_Sound_Play(0x06, 0);     // Play sound 19.
    
    CyDelay(3000);
    
    FT_Audio_Mute();
    FT_Sound_Stop();
}

/* [] END OF FILE */
