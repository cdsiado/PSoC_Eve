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
    EVE_Display_ON();
    mEVE_Register_Write(REG_PWM_DUTY, 128);
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
    // Test: CLEAR_COLOR_RGB, CLEAR
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0xFF, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    DLEndList();                                        // End the display list.
    CyDelay(1000);                              

    DLStartList();                             // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0xFF, 0x00)); // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                  // Clear all (color, stencil and tag buffer).
    DLEndList();                                     // End the display list.
    CyDelay(1000); 

    DLStartList();                             // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0xFF)); // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                  // Clear all (color, stencil and tag buffer).
    DLEndList();   
    CyDelay(1000); 

    DLStartList();                             // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00)); // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                  // Clear all (color, stencil and tag buffer).
    DLEndList(); 
}

void T_DL_PRIMITIVE_POINT()
{
    // Test also: DL_COLOR_RGB, DL_VERTEXII, DL_POINT_SIZE, DL_END,
    //     DL_LINE_WIDTH
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    DLListNewItem(DLColorRGB(0xFF, 0xFF, 0xFF));        // White color.
    DLListNewItem(DLBegin(PRIMITIVE_POINT));            // Begin a primitive (POINT)
    DLListNewItem(DLVertex2II(10, 10, 0, 0));           // First point.
    DLListNewItem(DLPointSize(50));                     // Increase point size.
    DLListNewItem(DLVertex2II(240, 136, 0, 0));         // Second point.
    DLEndList();
}

void T_DL_PRIMITIVE_LINE()
{
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
       
    // Test PRIMITIVE_LINE
    DLListNewItem(DLColorRGB(0xFF, 0x00, 0x00));         // Red color.       
    DLListNewItem(DLBegin(PRIMITIVE_LINE));              // Begin a primitive (LINE)
        DLListNewItem(DLVertex2II(10, 10, 0, 0));        // First point (line from...)
        DLListNewItem(DLVertex2II(100, 10, 0, 0));       // Second point (to...)
        DLListNewItem(DLColorRGB(0x00, 0xFF, 0x00));
    DLListNewItem(DLBegin(PRIMITIVE_LINE));
        DLListNewItem(DLLineWidth(3));
        DLListNewItem(DLVertex2II(10, 30, 0, 0));        // First point (line from...)
        DLListNewItem(DLVertex2II(100, 100, 0, 0));      // Second point (to...)
        DLListNewItem(DLEnd());
        DLListNewItem(DLColorRGB(0x00, 0x00, 0xFF));
        DLListNewItem(DLLineWidth(1));
    DLListNewItem(DLBegin(PRIMITIVE_LINE_STRIP));        // Begin a primitive (LINE_STRIP)
        DLListNewItem(DLVertex2II(200, 100, 0, 0));          
        DLListNewItem(DLVertex2II(300, 100, 0, 0));           
        DLListNewItem(DLVertex2II(300, 200, 0, 0));           
        DLListNewItem(DLVertex2II(200, 200, 0, 0));
        DLListNewItem(DLVertex2II(200, 100, 0, 0));
    DLEndList();
}

void T_PRIMITIVE_EDGESTRIP()
{
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).

    DLListNewItem(DLColorRGB(0xFF, 0xFF, 0xFF));
    DLListNewItem(DLLineWidth(1));
    DLListNewItem(DLBegin(PRIMITIVE_EDGE_STRIP_A));      // Begin a primitive (EDGE_STRIP_A)
        DLListNewItem(DLVertex2II(50, 50, 0, 0));        // First point (line from...)
        DLListNewItem(DLVertex2II(200, 70, 0, 0));       // Second point (to...)   

        DLListNewItem(DLColorRGB(0x00, 0xFF, 0x00));
    DLListNewItem(DLBegin(PRIMITIVE_EDGE_STRIP_L));      
        DLListNewItem(DLVertex2II(50, 70, 0, 0));           
        DLListNewItem(DLVertex2II(100, 90, 0, 0)); 
        DLListNewItem(DLVertex2II(50, 100, 0, 0));
        DLListNewItem(DLVertex2II(75, 200, 0, 0));
    
    DLListNewItem(DLBegin(PRIMITIVE_EDGE_STRIP_R));      
        DLListNewItem(DLVertex2II(400, 70, 0, 0));           
        DLListNewItem(DLVertex2II(350, 100, 0, 0)); 
        DLListNewItem(DLVertex2II(400, 200, 0, 0));
 
        DLListNewItem(DLColorRGB(0x00, 0x00, 0xFF));         
    DLListNewItem(DLBegin(PRIMITIVE_EDGE_STRIP_B));      
        DLListNewItem(DLVertex2II(200, 200, 0, 0));           
        DLListNewItem(DLVertex2II(350, 150, 0, 0)); 
    DLEndList();
}

void T_PRIMITIVE_RECTANGLE()
{
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
        DLListNewItem(DLColorRGB(0x00, 0xFF, 0x00));         
        DLListNewItem(DLLineWidth(1));
    DLListNewItem(DLBegin(PRIMITIVE_RECTANGLE));         
        DLListNewItem(DLVertex2II(40, 40, 0, 0));            
        DLListNewItem(DLVertex2II(100, 100, 0, 0));    
        DLListNewItem(DLColorRGB(0xFF, 0xFF, 0x00));         
        DLListNewItem(DLLineWidth(5));                  // Round rectangle
        DLListNewItem(DLBegin(PRIMITIVE_RECTANGLE));         
        DLListNewItem(DLVertex2II(200, 200, 0, 0));            
        DLListNewItem(DLVertex2II(300, 250, 0, 0));
    DLEndList();
}

void T_PRIMITIVE_BITMAP()
{
    unsigned int loop, bitmaplength;
    
    // Firt, copy the bitmap data from program memory to RAM_G (graphics RAM) of the 
    // EVE chip. Starting at address 0.
    bitmaplength = sizeof(testbitmap);
    SPI_Transfer_Start(RAM_G | MEMORY_WRITE);
    SPI_TransferL_Write_ByteArray(testbitmap, bitmaplength);
    SPI_Transfer_End();
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));            // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));             // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 40*2,40));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 40, 40)); 
        DLListNewItem(DLVertex2II(10, 10, 0, 0));        // Place the bitmap at 10, 10.
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 20, 20)); 
        DLListNewItem(DLVertex2II(100, 10, 0, 0));       // Place, only a piece of the bitmap.
    DLEndList();
    
    CyDelay(3000);
    
    // **********************************************************************    TODO: REvisar.
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));            // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));             // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 40*2,40));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_REPEAT, BITMAP_SIZE_WRAP_REPEAT, 480, 272)); 
        DLListNewItem(DLVertex2II(0, 0, 0, 0));          // Place the bitmap at 0, 0.
                                                        // Fill display.
    DLEndList();
    
    CyDelay(3000);
    
    // **********************************************************************    
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));           // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));            // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 40*2,40));
        DLListNewItem(DLBitmapTransformA(120));
        DLListNewItem(DLBitmapTransformE(120));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 120, 120)); 
        DLListNewItem(DLVertex2II(0, 0, 0, 0));         // Place the bitmap at 0, 0.
                                                        // Fill display.
    DLEndList();
    
    CyDelay(3000);
    
    // **********************************************************************    
            
        // The same with bilinear filter.
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));           // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));            // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 40*2,40));
        DLListNewItem(DLBitmapTransformA(160));
        DLListNewItem(DLBitmapTransformE(160));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_BILINEAR, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 240, 240)); 
        DLListNewItem(DLVertex2II(0, 0, 0, 0));         // Place the bitmap at 0, 0.
                                                        // Fill display.
    DLEndList();
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
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));    
    CMDListNewItem(CMDGradient(10, 10, 0, 0, 0xFF, 470, 262, 0xFF, 0x0, 0x0));   // TODO: verificar coordenadas
    CMDEndList(END_DL_SWAP);     
}

void T_CMD_TEXT()
{
    CMDStartList();
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDInsertDLItem(DLColorRGB(0xFF, 0x00, 0xFF));
    CMDListNewItem(CMDTextNew( 10, 10, 30, 0, "!Hello"));
    CMDInsertDLItem(DLColorRGB(0x00, 0x00, 0xFF));
    CMDListNewItem(CMDTextNew( 150, 150, 30, 0, "JESUSS25"));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_BUTTON()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListNewItem(CMDButton(20, 20, 100, 50, 28, OPT_3D, (unsigned char*)"3d"));
    CMDListNewItem(CMDGradcolor(0xFF, 0x00, 0x00)); // TODO: verificar.
    CMDListNewItem(CMDButton(50, 150, 100, 50, 28, OPT_FLAT, (unsigned char*)"flat"));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_KEYS()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));    
    CMDListNewItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListNewItem(CMDKeys(20, 20, 100, 50, 28, OPT_3D, (unsigned char*)"3d"));
    CMDListNewItem(CMDKeys(50, 150, 100, 50, 28, OPT_FLAT, (unsigned char*)"flat"));
    CMDEndList(END_DL_SWAP);  
}

void T_CMD_PROGRESS()
{
    CMDStartList();
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDBgcolor(0xFF, 0x00, 0x00));
    CMDListNewItem(CMDProgressBar(10, 10, 150, 20, OPT_3D, 50, 100)); // TODO: Coordenadas?
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SLIDER()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDFgcolor(0x00, 0xFF, 0x00));
    CMDListNewItem(CMDBgcolor(0xFF, 0x00, 0x00));
    CMDListNewItem(CMDSlider(10, 10, 150, 20, OPT_3D, 50, 100));
    CMDListNewItem(CMDSlider(10, 100, 200, 20, OPT_FLAT, 50, 200));  
    CMDListNewItem(CMDSlider(250, 10, 20, 150, OPT_3D, 50, 100));
    CMDListNewItem(CMDSlider(300, 10, 20, 200, OPT_FLAT, 50, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SCROLLBAR()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDFgcolor(0xFF, 0x00, 0x00));
    CMDListNewItem(CMDBgcolor(0x00, 0xFF, 0x00)); // <<<<< REVISAR
    CMDListNewItem(CMDScrollBar(10, 10, 150, 20, OPT_3D, 10, 40, 100));
    CMDListNewItem(CMDScrollBar(10, 100, 200, 20, OPT_FLAT, 10, 40, 100));  
    CMDListNewItem(CMDScrollBar(250, 10, 20, 150, OPT_3D, 10, 40, 200));
    CMDListNewItem(CMDScrollBar(300, 10, 20, 200, OPT_FLAT, 10, 40, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_TOGGLE()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));    
    CMDListNewItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListNewItem(CMDBgcolor(0x00, 0x00, 0xFF));
    CMDListNewItem(CMDToggle(50, 50, 200, 28, 0, TOGGLE_STATE_ON, (unsigned char*)"ON\xffOFF"));
    CMDListNewItem(CMDToggle(100, 100, 200, 28, 0, TOGGLE_STATE_OFF, (unsigned char*)"ON\xffOFF"));
    CMDEndList(END_DL_SWAP);    
}

void T_CMD_GAUGE()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDBgcolor(0x00, 0x00, 0xFF));
    CMDListNewItem(CMDGauge(70, 70, 50, OPT_3D, 5, 4, 30, 100));
    CMDListNewItem(CMDGauge(180, 70, 50, OPT_FLAT, 5, 4, 30, 100)); 
    CMDListNewItem(CMDGauge(290, 70, 50, OPT_3D, 10, 2, 30, 100));
    CMDListNewItem(CMDGauge(400, 70, 50, OPT_3D, 10, 1, 30, 100));
    CMDListNewItem(CMDGauge(70, 180, 50, OPT_3D, 1, 10, 30, 100));
    CMDListNewItem(CMDBgcolor(0x40, 0x20, 0x00));
    CMDListNewItem(CMDGauge(180, 180, 50, OPT_3D, 5, 4, 30, 100));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_CLOCK()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDBgcolor(0x00, 0x00, 0xFF)); // <<<<< REVISAR
    CMDListNewItem(CMDClock(70, 70, 50, OPT_3D, 15, 30, 42, 100));
    CMDListNewItem(CMDClock(180, 70, 50, OPT_FLAT, 2, 45, 53, 100));
    CMDEndList(END_DL_SWAP); 
}

void T_CMD_CALIBRATE()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDCalibrate());
    CMDEndList(END_DL_SWAP);  
    
    while (!FTIsCoproccesorReady()) {}
}

void T_CMD_SPINNER()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDInsertDLItem(DLColorRGB(0x55, 0xFF, 0x55));
    CMDListNewItem(CMDSpinner(240, 136, SPINNER_ROUND, 0));
    CMDEndList(END_DL_NOSWAP);
    
    CyDelay(5000);
    
    CMDStartList();
    CMDListNewItem(CMDStop());
    CMDEndList(END_DL_SWAP);
}

void T_CMD_DIAL()
{
    CMDStartList(); 
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDListNewItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListNewItem(CMDDial(70, 70, 50, OPT_3D, 30000));
    CMDListNewItem(CMDDial(180, 70, 50, OPT_FLAT, 40000));
    CMDEndList(END_DL_SWAP); 
}

void T_CMD_NUMBER()
{
    CMDStartList();
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDInsertDLItem(DLClear(1, 1, 1));
    CMDInsertDLItem(DLColorRGB(0xFF, 0x00, 0x00));
    CMDListNewItem(CMDNumber(10, 10, 28, 0, 100));
    CMDInsertDLItem(DLColorRGB(0x00, 0xFF, 0x00));
    CMDListNewItem(CMDNumber(40, 40, 30, OPT_SIGNED, -100));
    CMDInsertDLItem(DLColorRGB(0x00, 0x00, 0xFF));
    CMDListNewItem(CMDNumber(80, 80,30,0, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SKETCH()
{
    // Draw rectangle.
//    DLStartList();                                      // Start the display list.
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
//    DLEndList();
    
    // Skecth
    CMDStartList();
    
    CMDInsertDLItem(DLClearColorRGB(0x00, 0x00, 0x00));     // Set red color for background. 
    CMDInsertDLItem(DLClear(1, 1, 1));                      // Clear all (color, stencil and tag buffer).
    CMDInsertDLItem(DLColorRGB(0x00, 0xFF, 0x00));          // Red color. 
    
        CMDInsertDLItem(DLLineWidth(1));                    // Draw green rectangle as sketching area.
    CMDInsertDLItem(DLBegin(PRIMITIVE_LINE_STRIP));        
        CMDInsertDLItem(DLVertex2II(20, 20, 0, 0));          
        CMDInsertDLItem(DLVertex2II(300, 20, 0, 0));           
        CMDInsertDLItem(DLVertex2II(300, 250, 0, 0));           
        CMDInsertDLItem(DLVertex2II(20, 250, 0, 0));
        CMDInsertDLItem(DLVertex2II(20, 20, 0, 0));
        
    CMDInsertDLItem(DLTag(1));                              // Place "exit" button with tag=1 for touches.
    CMDListNewItem(CMDButton(350, 50, 100, 50, 28, OPT_3D, (unsigned char*)"Exit"));
    CMDInsertDLItem(DLTagMask(0));
    
    CMDInsertDLItem(DLColorRGB(0xFF, 0xFF, 0xFF));
    CMDListNewItem(CMDMemZero(0, (LCDWIDTH * LCDHEIGHT / 8)));  // Fill with zeroes area used to store the sketch
    CMDListNewItem(CMDSketch(21, 21, 299, 249, 0, L1));         // Start sketch
    CMDEndList(END_DL_SWAP);
    
    CyDelay(20000); // 20 seconds to draw
    
    CMDStartList();
    CMDListNewItem(CMDStop());
    CMDEndList(END_DL_SWAP);
}

/* [] END OF FILE */
