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
#include "Test.h"

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
    T_CMD_COLDSTART();
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
    T_CMD_COLDSTART();
    
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
    T_CMD_COLDSTART();
    
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
    T_CMD_COLDSTART();
    
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
    unsigned int bitmaplength;
    
    T_CMD_COLDSTART();
    
    // Firt, copy the bitmap data from program memory to RAM_G (graphics RAM) of the 
    // EVE chip. Starting at address 0.
    bitmaplength = sizeof(testbitmap);
    FT_Transfer_Start(RAM_G | MEMORY_WRITE);
    FT_Send_ByteArray(testbitmap, bitmaplength);
    FT_Transfer_End();
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));            // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));             // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64)); 
        DLListNewItem(DLVertex2II(10, 10, 0, 0));        // Place the bitmap at 10, 10.
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 32, 32)); 
        DLListNewItem(DLVertex2II(100, 10, 0, 0));       // Place, only a piece of the bitmap.
    DLEndList();
    
    CyDelay(3000);
    
    // **********************************************************************    TODO: REvisar.
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));            // Start new primitive (BITMAP.
        DLListNewItem(DLBitmapSource(0x00));             // Source address 0 in RAM_G.
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
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
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
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
        DLListNewItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
        DLListNewItem(DLBitmapTransformA(160));
        DLListNewItem(DLBitmapTransformE(160));
        DLListNewItem(DLBitmapSize(BITMAP_SIZE_FILTER_BILINEAR, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 240, 240)); 
        DLListNewItem(DLVertex2II(0, 0, 0, 0));         // Place the bitmap at 0, 0.
                                                        // Fill display.
    DLEndList();
}

void T_DL_B() // Test DL_COLOR_A, DL_BLEND_FUNC
{
    T_CMD_COLDSTART();
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
        DLListNewItem(DLColorRGB(0xFF, 0x00, 0x00));         
        DLListNewItem(DLLineWidth(1));
    DLListNewItem(DLBegin(PRIMITIVE_RECTANGLE));         
        DLListNewItem(DLVertex2II(20, 100, 0, 0));            
        DLListNewItem(DLVertex2II(470, 150, 0, 0));   
        DLListNewItem(DLColorRGB(0xFF, 0xFF, 0xFF));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(40, 100, 31, 0x47)); 
        DLListNewItem(DLColorA(128));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(80, 100, 31, 0x47)); 
        DLListNewItem(DLColorA(64));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(120, 100, 31, 0x47));    
        DLListNewItem(DLColorA(255));
    DLEndList();    
    
    CyDelay(3000);
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   // Set red color for background. 
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
        DLListNewItem(DLColorRGB(0xFF, 0x00, 0x00));         
        DLListNewItem(DLLineWidth(1));
    DLListNewItem(DLBegin(PRIMITIVE_RECTANGLE));         
        DLListNewItem(DLVertex2II(20, 100, 0, 0));            
        DLListNewItem(DLVertex2II(470, 150, 0, 0));   
        DLListNewItem(DLColorRGB(0xFF, 0xFF, 0xFF));
        DLListNewItem(DLColorA(128));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(40, 100, 31, 0x47)); 
        DLListNewItem(DLBlendFunc(BLEND_FUNC_SRC_ALPHA, BLEND_FUNC_ZERO));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(80, 100, 31, 0x47));
        DLListNewItem(DLBlendFunc(BLEND_FUNC_ZERO, BLEND_FUNC_SRC_ALPHA));
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
        DLListNewItem(DLVertex2II(120, 100, 31, 0x47));    
        DLListNewItem(DLColorA(255));
    DLEndList();
}

void T_DL_SCISSOR()
{
    T_CMD_COLDSTART();
    
    DLStartList();                                      // Start the display list.
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0x00));   
    DLListNewItem(DLClear(1, 1, 1));                    // Clear all (color, stencil and tag buffer).
    DLListNewItem(DLScissorXY(40, 30));         
    DLListNewItem(DLScissorSize(80, 60));
    DLListNewItem(DLClearColorRGB(0x00, 0x00, 0xFF));   
    DLListNewItem(DLClear(1, 1, 1));      
    DLListNewItem(DLBegin(PRIMITIVE_BITMAP));         
    DLListNewItem(DLVertex2II(35, 20, 31, 0x47));
    DLEndList();    
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
        CMDStartList(); 
        CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
        CMDListAddDLItem(DLClear(1, 1, 1));
        
        CMDListAddDLItem(DLTagMask(1));
        
        CMDListAddDLItem(DLTag(1));
        CMDListAddDLItem(DLColorRGB((uint8)(firstrectanglecolor >> 16), (uint8)(firstrectanglecolor >> 8), (uint8)(firstrectanglecolor)));
        CMDListAddDLItem(DLBegin(PRIMITIVE_RECTANGLE));         
        CMDListAddDLItem(DLVertex2II(50, 50, 0, 0));            
        CMDListAddDLItem(DLVertex2II(100, 100, 0, 0));    

        CMDListAddDLItem(DLTag(2));
        CMDListAddDLItem(DLColorRGB((uint8)(secondrectanglecolor >> 16), (uint8)(secondrectanglecolor >> 8), (uint8)(secondrectanglecolor)));
        CMDListAddDLItem(DLBegin(PRIMITIVE_RECTANGLE));         
        CMDListAddDLItem(DLVertex2II(150, 50, 0, 0));            
        CMDListAddDLItem(DLVertex2II(200, 100, 0, 0));   
        
        CMDListAddDLItem(DLTagMask(0));
        CMDListAddDLItem(DLColorRGB(0xFF, 0xFF, 0xFF));
        CMDListAddDLItem(DLBegin(PRIMITIVE_RECTANGLE));         
        CMDListAddDLItem(DLVertex2II(250, 50, 0, 0));            
        CMDListAddDLItem(DLVertex2II(300, 100, 0, 0));      
        
        CMDListAddDLItem(DLTagMask(1));
        
        CMDListAddDLItem(DLTag(3));
        CMDListAddItem(CMDFgcolor(0xFF, 0xFF, 0x00));
        CMDListAddItem(CMDButton(50, 200, 100, 50, 28, OPT_3D, (unsigned char*)"EXIT"));
        CMDEndList(END_DL_SWAP);
        
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
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));    
    CMDListAddItem(CMDGradient(0, 0, 0, 0, 0xFF, 160, 0, 0xFF, 0x0, 0x0));
    CMDEndList(END_DL_SWAP);     
}

void T_CMD_TEXT()
{
    T_CMD_COLDSTART();
    
    CMDStartList();
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddDLItem(DLColorRGB(0xFF, 0x00, 0xFF));
    CMDListAddItem(CMDTextNew( 10, 10, 30, 0, "!Hello"));
    CMDListAddDLItem(DLColorRGB(0x00, 0x00, 0xFF));
    CMDListAddItem(CMDTextNew( 150, 150, 30, 0, "JESUSS25"));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_BUTTON()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListAddItem(CMDButton(20, 20, 100, 50, 28, OPT_3D, (unsigned char*)"3d"));
    CMDListAddItem(CMDGradcolor(0xFF, 0x00, 0x00)); // TODO: verificar.
    CMDListAddItem(CMDButton(50, 150, 100, 50, 28, OPT_FLAT, (unsigned char*)"flat"));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_KEYS()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));    
    CMDListAddItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListAddItem(CMDKeys(20, 20, 100, 50, 28, OPT_3D, (unsigned char*)"3d"));
    CMDListAddItem(CMDKeys(50, 150, 100, 50, 28, OPT_FLAT, (unsigned char*)"flat"));
    CMDEndList(END_DL_SWAP);  
}

void T_CMD_PROGRESS()
{
    T_CMD_COLDSTART();
    
    CMDStartList();
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDBgcolor(0xFF, 0x00, 0x00));
    CMDListAddItem(CMDProgressBar(10, 10, 150, 20, OPT_3D, 50, 100)); // TODO: Coordenadas?
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SLIDER()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDFgcolor(0x00, 0xFF, 0x00));
    CMDListAddItem(CMDBgcolor(0xFF, 0x00, 0x00));
    CMDListAddItem(CMDSlider(10, 10, 150, 20, OPT_3D, 50, 100));
    CMDListAddItem(CMDSlider(10, 100, 200, 20, OPT_FLAT, 50, 200));  
    CMDListAddItem(CMDSlider(250, 10, 20, 150, OPT_3D, 50, 100));
    CMDListAddItem(CMDSlider(300, 10, 20, 200, OPT_FLAT, 50, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SCROLLBAR()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDFgcolor(0xFF, 0x00, 0x00));
    CMDListAddItem(CMDBgcolor(0x00, 0xFF, 0x00)); // <<<<< REVISAR
    CMDListAddItem(CMDScrollBar(10, 10, 150, 20, OPT_3D, 10, 40, 100));
    CMDListAddItem(CMDScrollBar(10, 100, 200, 20, OPT_FLAT, 10, 40, 100));  
    CMDListAddItem(CMDScrollBar(250, 10, 20, 150, OPT_3D, 10, 40, 200));
    CMDListAddItem(CMDScrollBar(300, 10, 20, 200, OPT_FLAT, 10, 40, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_TOGGLE()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));    
    CMDListAddItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListAddItem(CMDBgcolor(0x00, 0x00, 0xFF));
    CMDListAddItem(CMDToggle(50, 50, 200, 28, 0, TOGGLE_STATE_ON, (unsigned char*)"ON\xffOFF"));
    CMDListAddItem(CMDToggle(100, 100, 200, 28, 0, TOGGLE_STATE_OFF, (unsigned char*)"ON\xffOFF"));
    CMDEndList(END_DL_SWAP);    
}

void T_CMD_GAUGE()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDBgcolor(0x00, 0x00, 0xFF));
    CMDListAddItem(CMDGauge(70, 70, 50, OPT_3D, 5, 4, 30, 100));
    CMDListAddItem(CMDGauge(180, 70, 50, OPT_FLAT, 5, 4, 30, 100)); 
    CMDListAddItem(CMDGauge(290, 70, 50, OPT_3D, 10, 2, 30, 100));
    CMDListAddItem(CMDGauge(400, 70, 50, OPT_3D, 10, 1, 30, 100));
    CMDListAddItem(CMDGauge(70, 180, 50, OPT_3D, 1, 10, 30, 100));
    CMDListAddItem(CMDBgcolor(0x40, 0x20, 0x00));
    CMDListAddItem(CMDGauge(180, 180, 50, OPT_3D, 5, 4, 30, 100));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_CLOCK()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDBgcolor(0x00, 0x00, 0xFF)); // <<<<< REVISAR
    CMDListAddItem(CMDClock(70, 70, 50, OPT_3D, 15, 30, 42, 100));
    CMDListAddItem(CMDClock(180, 70, 50, OPT_FLAT, 2, 45, 53, 100));
    CMDEndList(END_DL_SWAP); 
}

void T_CMD_CALIBRATE()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDCalibrate());
    CMDEndList(END_DL_SWAP);  
    
    while (!FTIsCoproccesorReady()) {}
}

void T_CMD_SPINNER()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddDLItem(DLColorRGB(0x55, 0xFF, 0x55));
    CMDListAddItem(CMDSpinner(240, 136, SPINNER_ROUND, 0));
    CMDEndList(END_DL_NOSWAP);
    
    CyDelay(5000);
    
    CMDStartList();
    CMDListAddItem(CMDStop());
    CMDEndList(END_DL_SWAP);
}

void T_CMD_DIAL()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDFgcolor(0xFF, 0xFF, 0x00));
    CMDListAddItem(CMDDial(70, 70, 50, OPT_3D, 30000));
    CMDListAddItem(CMDDial(180, 70, 50, OPT_FLAT, 40000));
    CMDEndList(END_DL_SWAP); 
}

void T_CMD_NUMBER()
{
    T_CMD_COLDSTART();
    
    CMDStartList();
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddDLItem(DLColorRGB(0xFF, 0x00, 0x00));
    CMDListAddItem(CMDNumber(10, 10, 28, 0, 100));
    CMDListAddDLItem(DLColorRGB(0x00, 0xFF, 0x00));
    CMDListAddItem(CMDNumber(40, 40, 30, OPT_SIGNED, -100));
    CMDListAddDLItem(DLColorRGB(0x00, 0x00, 0xFF));
    CMDListAddItem(CMDNumber(80, 80,30,0, 200));
    CMDEndList(END_DL_SWAP);
}

void T_CMD_SKETCH()
{
    T_CMD_COLDSTART();
    
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
    
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));     // Set red color for background. 
    CMDListAddDLItem(DLClear(1, 1, 1));                      // Clear all (color, stencil and tag buffer).
    CMDListAddDLItem(DLColorRGB(0x00, 0xFF, 0x00));          // Red color. 
    
        CMDListAddDLItem(DLLineWidth(1));                    // Draw green rectangle as sketching area.
    CMDListAddDLItem(DLBegin(PRIMITIVE_LINE_STRIP));        
        CMDListAddDLItem(DLVertex2II(20, 20, 0, 0));          
        CMDListAddDLItem(DLVertex2II(300, 20, 0, 0));           
        CMDListAddDLItem(DLVertex2II(300, 250, 0, 0));           
        CMDListAddDLItem(DLVertex2II(20, 250, 0, 0));
        CMDListAddDLItem(DLVertex2II(20, 20, 0, 0));
        
    CMDListAddDLItem(DLTag(1));                              // Place "exit" button with tag=1 for touches.
    CMDListAddItem(CMDButton(350, 50, 100, 50, 28, OPT_3D, (unsigned char*)"Exit"));
    CMDListAddDLItem(DLTagMask(0));
    
    CMDListAddDLItem(DLColorRGB(0xFF, 0xFF, 0xFF));
    CMDListAddItem(CMDMemZero(0, (LCDWIDTH * LCDHEIGHT / 8)));          // Fill with zeroes area used to store the sketch
    CMDListAddItem(CMDSketch(21, 21, 299, 249, 0, BITMAP_LAYOUT_L1));   // Start sketch
    CMDEndList(END_DL_SWAP);
    
    CyDelay(20000); // 20 seconds to draw
    
    CMDStartList();
    CMDListAddItem(CMDStop());
    CMDEndList(END_DL_SWAP);
}

void T_CMD_LOGO()
{
    T_CMD_COLDSTART();
    
    CMDStartList(); 
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddItem(CMDLogo());
    CMDEndList(END_DL_SWAP);  
    
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
        
    CMDStartList(); 
    CMDListAddItem(CMDScreenSaver());
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddDLItem(DLBegin(PRIMITIVE_BITMAP));        // Start new primitive (BITMAP.
    CMDListAddDLItem(DLBitmapSource(0x00));             // Source address 0 in RAM_G.
    CMDListAddDLItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
    CMDListAddDLItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64)); 
    CMDListAddDLItem(DLMacro(0));
    CMDEndList(END_DL_SWAP);    
    
    CyDelay(10000); // Wait 10 seconds, then stop screensaver.
    
    CMDStartList();
    CMDListAddItem(CMDStop());
    CMDEndList(END_DL_SWAP);    
}

void T_CMD_COLDSTART()
{
    CMDStartList();
    CMDListAddItem(CMDColdstart());
    CMDEndList(END_DL_SWAP); 
    
    CyDelay(5);
}

void T_CMD_INFLATE()
{
    unsigned int bitmaplength;
    
    T_CMD_COLDSTART();    
    
    bitmaplength = sizeof(testbitmapzlib);
    
    CMDStartList(); 
    CMDListAddItem(CMDInflate(RAM_G));                     // Inflate data in RAM_G memory.
    FT_Write_ByteArray_4(testbitmapzlib, bitmaplength);    // Send Zlib data. 
    
    CMDListAddDLItem(DLClearColorRGB(0x00, 0x00, 0x00));
    CMDListAddDLItem(DLClear(1, 1, 1));
    CMDListAddDLItem(DLBegin(PRIMITIVE_BITMAP));             // Start new primitive (BITMAP.
    CMDListAddDLItem(DLBitmapSource(0x00));                  // Source address 0 in RAM_G.
    CMDListAddDLItem(DLBitmapLayout(BITMAP_LAYOUT_RGB565, 64*2, 64));
    CMDListAddDLItem(DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 64, 64)); 
    CMDListAddDLItem(DLVertex2F(100, 100));
    CMDEndList(END_DL_SWAP);     
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
