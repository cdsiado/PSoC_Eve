/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <project.h>
#include "..\..\..\PSoCEveLibrary\PsoCEve.h"
#include "resources.h"
#include "demo_sketch.h"

static uint8 skey = 0;

/* Function prototypes. */
uint8 Read_Keys();

void Home_Setup()
{
    /* Initialize LCD Display. 
        If initialization fails, turn on red led and program gets locked. 
        If initialization sucessful then turn on green led.
    */
    if (!FT_Init())
    {
        Led_Red_Write(0);       // Init failed. Turn on red led.
        while(1);
    }
   
    Led_Green_Write(0);         // Init ok. Turn on green led.
    
    // Turn on display and backlight.
    FT_Display_ON();
    FT_Register_Write(REG_PWM_DUTY, 128);
    
    // Copy image from flash (resources) to RAM_G.
    FT_ListStart(COPROCESSOR);
        CMDInflate(250 * 1024);
        FT_Write_ByteArray_4(home_star_icon, sizeof(home_star_icon));
    FT_ListEnd(END_DL_NOSWAP);

    // Display list.
    FT_ListStart(DISPLAY);
        DLClear(1, 1, 1);
        DLColorRGB(255, 255, 255);
        DLBitmapHandle(13);
        DLBitmapSource(250 * 1024);
        DLBitmapLayout(BITMAP_LAYOUT_L4, 16, 32);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_REPEAT, BITMAP_SIZE_WRAP_REPEAT, 512, 512);
        DLBitmapHandle(14);
        DLBitmapSource(250 * 1024);
        DLBitmapLayout(BITMAP_LAYOUT_L4, 16, 32);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, 32, 32);
    FT_ListEnd(END_DL_SWAP);
}

void Info()
{
    // Info Screen.
    
    // Touch calibratrion.
    FT_ListStart(COPROCESSOR);
        DLClear(1, 1, 1);
        DLColorRGB(255, 255, 255);
        CMDText(LCDWIDTH / 2, LCDHEIGHT / 2, 26, OPT_CENTERX | OPT_CENTERY, "Please tap on a dot.");
        FT_Touch_Calibrate();
    FT_ListEnd(END_DL_SWAP);
    FT_Touch_WaitCalibrationEnds();
    
    // FTDI Logo animation.
    FT_ListStart(COPROCESSOR);
        CMDLogo();
    FT_ListEnd(END_DL_SWAP);
    CyDelay(3000);
        
    do
    {
        FT_ListStart(COPROCESSOR);
            DLClearColorRGB(0x00, 0x00, 0x00);
            DLClear(1, 1, 1);
            DLColorRGB(0xFF, 0x00, 0xFF);
            CMDText(LCDWIDTH/2, 20, 28, OPT_CENTERX | OPT_CENTERY, "FT800 Sketch Application");
            CMDText(LCDWIDTH/2, 60, 26, OPT_CENTERX | OPT_CENTERY, "APP to demonstrate interactive Sketch,");
            CMDText(LCDWIDTH/2, 90, 26, OPT_CENTERX | OPT_CENTERY, "using Sketch, Slider,");
            CMDText(LCDWIDTH/2, 120, 26, OPT_CENTERX | OPT_CENTERY, "& Buttons.");
            CMDText(LCDWIDTH/2, LCDHEIGHT - 30, 26, OPT_CENTERX | OPT_CENTERY, "Click to play");
            
            if (skey != 'P')
                DLColorRGB(255, 255, 255);
            else
                DLColorRGB(100, 100, 100);
                
            DLBegin(PRIMITIVE_POINT);
                DLPointSize(20 * 16);
                DLTag('P');
                DLVertex2F((LCDWIDTH / 2) * 16, (LCDHEIGHT - 60) * 16);
            DLColorRGB(180, 35, 35);
            DLBegin(PRIMITIVE_BITMAP);
                
            #if defined LCD_WVVGA
                DLBitmapHandle(14);
                DLCell(4);
                DLVertex2F((LCDWIDTH / 2 - 14) * 16, (LCDHEIGHT - 75) * 16);
            #else
                DLVertex2II((LCDWIDTH / 2) - 14,(LCDHEIGHT - 75), 14, 4);
            #endif
            
        FT_ListEnd(END_DL_SWAP);

    } while (Read_Keys() != 'P');

    FT_Audio_Unmute();
    FT_Sound_Volume(255);
    FT_Sound_Play(0x50, 0xc0);    
}

uint8 Read_Keys()
{
    static uint8 read_tag = 0, temp_tag = 0, ret_tag = 0;
    
    read_tag = FT_Register_Read(REG_TOUCH_TAG);
    ret_tag = 0;
    
    if (read_tag != 0)
    {
        if (temp_tag != read_tag)
        {
            temp_tag = read_tag;
            skey = read_tag;
        }
    }
    else
    {
        if (temp_tag != 0)
        {
            ret_tag = temp_tag;
        }
        
        skey = 0;
    }
    
    return ret_tag;
}

void Sketch()
{
    uint32 tracker, color = 0;
    uint16 val = 32768;
    uint8 tag = 0;
    
    //  Set the bitmap properties , sketch properties and Tracker for the sliders
    FT_ListStart(COPROCESSOR);
        CMDFgcolor(0xFF, 0xFF, 0xFF);
        CMDTrack(LCDWIDTH - 30, 40, 8, LCDHEIGHT - 100, 1);
        CMDSketch(0, 10, LCDWIDTH - 40, LCDHEIGHT - 30, 0, BITMAP_LAYOUT_L8);
        CMDMemZero(0, (LCDWIDTH - 40) * (LCDHEIGHT - 20));
        DLBitmapHandle(1);
        DLBitmapSource(0);
        DLBitmapLayout(BITMAP_LAYOUT_L8, LCDWIDTH - 40, LCDHEIGHT - 20);
        DLBitmapSize(BITMAP_SIZE_FILTER_NEAREST, BITMAP_SIZE_WRAP_BORDER, BITMAP_SIZE_WRAP_BORDER, LCDWIDTH - 40, LCDHEIGHT - 20);
    FT_ListEnd(END_DL_SWAP);

    while(1)
    {
        // Check the tracker
        tracker = FT_Register_Read(REG_TRACKER);
        
        // Check the tag.
        tag = FT_Register_Read(REG_TOUCH_TAG);
        
        // Clear G-RAM when user enter the Clear button.
        if (tag == 2)
        {
            FT_ListStart(COPROCESSOR);
                CMDMemZero(0, (LCDWIDTH - 40) * (LCDHEIGHT - 20));
            FT_ListEnd(END_DL_SWAP);
        }
        
        // Compute  color from tracker.
        if ((tracker & 0xFF) == 1)
        {
            val = tracker >> 16;
        }
        
        color = val * 255;

        // Start new display list.
        FT_ListStart(COPROCESSOR);
            DLClear(1, 1, 1);
            DLColorRGB(255, 255, 255);
            CMDBgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
            DLTagMask(1);
            DLTag(1);
            CMDFgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
        
            // Draw the sliders.
            CMDSlider(LCDWIDTH - 30, 40, 8, LCDHEIGHT - 100, 0, val, 65535);
            
            if (tag == 2)
                CMDFgcolor(0x00, 0x00, 0xFF);
            else
                CMDFgcolor((color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, (color & 0x000000FF));
                
            DLTag(2);
            CMDButton(LCDWIDTH - 35, LCDHEIGHT - 45, 35, 25, 26, 0, "CLR");
            DLTagMask(0);
        
            CMDText(LCDWIDTH - 35, 10, 26, 0, "Color");
            
            DLLineWidth(1 * 16);
            DLBegin(PRIMITIVE_RECTANGLE);
                DLVertex2F(0, 10 * 16);
                DLVertex2F((int16)((LCDWIDTH - 40) * 16), (int16)((LCDHEIGHT - 20) * 16));
		    DLColorRGB((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
            DLBegin(PRIMITIVE_BITMAP);
                DLVertex2II(0, 10, 1, 0);
            DLEnd();
        FT_ListEnd(END_DL_SWAP);
    }

}

/* [] END OF FILE */
