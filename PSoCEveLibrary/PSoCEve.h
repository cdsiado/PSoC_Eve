/*******************************************************************************
* File Name: PSoCEve.h  
* Version 0.1 Alpha
*
* Description:
*  PSoCEveLibrary project.
*  Library to easy the use of the FT EVE graphic chips from FTDI.
*  Actually in development and in a very early stage there is support only
*  for the FT800 chip with Cypress PSOC4 family microcontrollers.
*  It is planned to had support for FT801 and newer TF81x chips, also for
*  other PSOC families (PSOC3 and PSCO5).
*
* Note:
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This library is dual licensed under the MIT and GPL licenses.
* http:
*******************************************************************************/

#if !defined(PSOCEVE_LIBRARY_H)
#define PSOCEVE_LIBRARY_H
    
#define PSOCEVE_LIBRARY_VERSION     "0.1.0" 
    
#include <cytypes.h> 
#include "PSoCEve_Config.h"
#include "PSoCEve_Hal.h"
  
    
/*******************************************************************************
*   EVE Memory Map Addresses
*******************************************************************************/  

#define RAM_G           0x000000    // Main graphics RAM.
#define ROM_CHIPID      0x0C0000    // Chip ID and revision.
#define ROM_FONT        0x0BB23C    // Font table and bitmaps.
#define ROM_FONT_ADDR   0x0FFFFC    // Font table pointer address,
#define RAM_DL          0x100000    // Display list RAM.   
#define RAM_PAL         0x102000    // Palette RAM.  
#define RAM_REG         0x102400    // Registers.
#define RAM_CMD         0x108000    // Coprocessor command buffer.        
    
/*******************************************************************************
*   EVE Registers Addresses
*******************************************************************************/     
    
#define REG_ID                  0x102400 
#define REG_FRAMES              0x102404    
#define REG_CLOCK               0x102408    
#define REG_FREQUENCY           0x10240c
#define REG_RENDERMODE          0x102410
#define REG_SNAPY               0x102414    
#define REG_SNAPSHOT            0x102418    
#define REG_CPURESET            0x10241c    
#define REG_TAP_CRC             0x102420
#define REG_TAP_MASK            0x102424    
#define REG_HCYCLE              0x102428
#define REG_HOFFSET             0x10242c
#define REG_HSIZE               0x102430
#define REG_HSYNC0              0x102434
#define REG_HSYNC1              0x102438 
#define REG_VCYCLE              0x10243c 
#define REG_VOFFSET             0x102440    
#define REG_VSIZE               0x102444
#define REG_VSYNC0              0x102448
#define REG_VSYNC1              0x10244c     
#define REG_DLSWAP              0x102450    
#define REG_ROTATE              0x102454  
#define REG_OUTBITS             0x102458    
#define REG_DITHER              0x10245c
#define REG_SWIZZLE             0x102460    
#define REG_CSPREAD             0x102464
#define REG_PCLK_POL            0x102468
#define REG_PCLK                0x10246c
#define REG_TAG_X               0x102470    
#define REG_TAG_Y               0x102474
#define REG_TAG                 0x102478
#define REG_VOL_PB              0x10247c    
#define REG_VOL_SOUND           0x102480    
#define REG_SOUND               0x102484    
#define REG_PLAY                0x102488    
#define REG_GPIO_DIR            0x10248c
#define REG_GPIO                0x102490  
#define REG_INT_FLAGS           0x102498
#define REG_INT_EN              0x10249c
#define REG_INT_MASK            0x1024a0
#define REG_PLAYBACK_START      0x1024a4    
#define REG_PLAYBACK_LENGTH     0x1024a8   
#define REG_PLAYBACK_READPTR    0x1024ac 
#define REG_PLAYBACK_FREQ       0x1024b0
#define REG_PLAYBACK_FORMAT     0x1024b4
#define REG_PLAYBACK_LOOP       0x1024b8
#define REG_PLAYBACK_PLAY       0x1024bc 
#define REG_PWM_HZ              0x1024c0
#define REG_PWM_DUTY            0x1024c4
#define REG_MACRO_0             0x1024c8    
#define REG_MACRO_1             0x1024cc
#define REG_CMD_READ            0x1024e4
#define REG_CMD_WRITE           0x1024e8
#define REG_CMD_DL              0x1024ec     
#define REG_TOUCH_MODE          0x1024f0    
#define REG_TOUCH_ADC_MODE      0x1024f4
#define REG_TOUCH_CHARGE        0x1024f8
#define REG_TOUCH_SETTLE        0x1024fc    
#define REG_TOUCH_OVERSAMPLE    0x102500
#define REG_TOUCH_RZTHRESH      0x102504    
#define REG_TOUCH_RAW_XY        0x102508
#define REG_TOUCH_RZ            0x10250c
#define REG_TOUCH_SCREEN_XY     0x102510    
#define REG_TOUCH_TAG_XY        0x102514    
#define REG_TOUCH_TAG           0x102518 
#define REG_TOUCH_TRANSFORM_A   0x10251c    
#define REG_TOUCH_TRANSFORM_B   0x102520
#define REG_TOUCH_TRANSFORM_C   0x102524
#define REG_TOUCH_TRANSFORM_D   0x102528 
#define REG_TOUCH_TRANSFORM_E   0x10252c    
#define REG_TOUCH_TRANSFORM_F   0x102530
#define REG_TOUCH_DIRECT_XY     0x102574
#define REG_TOUCH_DIRECT_Z1Z2   0x102578
#define REG_TRACKER             0x109000
    
/*******************************************************************************
*   EVE Chip Commands
*******************************************************************************/    
    
#define FT800_ACTIVE    0x00			// Initializes FT800
#define FT800_STANDBY	0x41			// Place FT800 in Standby (clk running)
#define FT800_SLEEP		0x42			// Place FT800 in Sleep (clk off)
#define FT800_PWRDOWN	0x50			// Place FT800 in Power Down (core off)
#define FT800_CLKEXT	0x44			// Select external clock source
#define FT800_CLK48M	0x62			// Select 48MHz PLL
#define FT800_CLK36M	0x61			// Select 36MHz PLL
#define FT800_CORERST	0x68			// Reset core - all registers default  
    
    // FT800 Memory Commands.
#define MEMORY_WRITE    0x800000	    // FT800 Host Memory Write 
#define MEMORY_READ		0x000000		// FT800 Host Memory Read    
    
/*******************************************************************************
*   Definitions related to touch panel
*******************************************************************************/    

#define TOUCHMODE_OFF         0
#define TOUCHMODE_ONESHOT     1  
#define TOUCHMODE_FRAME       2
#define TOUCHMODE_CONTINUOUS  3    
    
/*******************************************************************************
*   Definition of constants for EVE_CoPro_EndDisplayList
*******************************************************************************/  
    
#define END_DL_NOSWAP   0    
#define END_DL_SWAP     1    
    
/*******************************************************************************
*   Macro definitions
*******************************************************************************/    
    
/* Write value to EVE register. */
#define FT_Register_Write(everegister, value) SPI_TransferS_Write_Long(everegister | MEMORY_WRITE, value)
    
/* Read value from EVE register. */
#define FT_Register_Read(everegister) SPI_TransferS_Read_Long(everegister | MEMORY_READ)      
    
    
//**********************************************************************************    
//********************************************************************************** 
//********************************************************************************** 
//********************************************************************************** 
//**********************************************************************************     
    
/*******************************************************************************
*   Definition of contants for primitive type
*******************************************************************************/ 
    
#define PRIMITIVE_BITMAP        1
#define PRIMITIVE_POINT         2
#define PRIMITIVE_LINE          3
#define PRIMITIVE_LINE_STRIP    4
#define PRIMITIVE_EDGE_STRIP_R  5
#define PRIMITIVE_EDGE_STRIP_L  6
#define PRIMITIVE_EDGE_STRIP_A  7
#define PRIMITIVE_EDGE_STRIP_B  8
#define PRIMITIVE_RECTANGLE     9    
    
/*******************************************************************************
*   Definition of contants for the command BITMAP_LAYOUT
*******************************************************************************/     
    
#define BITMAP_LAYOUT_ARGB1555  0    
#define BITMAP_LAYOUT_L1        1
#define BITMAP_LAYOUT_L4        2
#define BITMAP_LAYOUT_L8        3
#define BITMAP_LAYOUT_RGB332    4
#define BITMAP_LAYOUT_ARGB2     5
#define BITMAP_LAYOUT_ARGB4     6
#define BITMAP_LAYOUT_RGB565    7  
#define BITMAP_LAYOUT_PALETTED  8
#define BITMAP_LAYOUT_TEXT8X8   9
#define BITMAP_LAYOUT_TEXTVGA   10
#define BITMAP_LAYOUT_BARGRAPH  11    
    
/*******************************************************************************
*   Definition of contants for the command BITMAP_SIZE
*******************************************************************************/ 
    
#define BITMAP_SIZE_FILTER_NEAREST      0 
#define BITMAP_SIZE_FILTER_BILINEAR     1 
#define BITMAP_SIZE_WRAP_BORDER         0
#define BITMAP_SIZE_WRAP_REPEAT         1    
    
/*******************************************************************************
*   Definition of contants for the command ALPHA_FUNC
*******************************************************************************/
    
#define ALPHA_FUNC_NEVER        0
#define ALPHA_FUNC_LESS         1
#define ALPHA_FUNC_LEQUAL       2
#define ALPHA_FUNC_GREATER      3
#define ALPHA_FUNC_GEQUAL       4
#define ALPHA_FUNC_EQUAL        5
#define ALPHA_FUNC_NOTEQUAL     6
#define ALPHA_FUNC_ALLWAYS      7     
    
/*******************************************************************************
*   Definition of contants for the command STENCIL_FUNC
*******************************************************************************/  
    
#define STENCIL_FUNC_NEVER      0
#define STENCIL_FUNC_LESS       1
#define STENCIL_FUNC_LEQUAL     2
#define STENCIL_FUNC_GREATER    3
#define STENCIL_FUNC_GEQUAL     4
#define STENCIL_FUNC_EQUAL      5
#define STENCIL_FUNC_NOTEQUAL   6
#define STENCIL_FUNC_ALLWAYS    7    
    
/*******************************************************************************
*   Definition of contants for the command BLEND_FUNC
*******************************************************************************/  
    
#define BLEND_FUNC_ZERO                  0
#define BLEND_FUNC_ONE                   1
#define BLEND_FUNC_SRC_ALPHA             2
#define BLEND_FUNC_DST_ALPHA             3
#define BLEND_FUNC_ONE_MINUS_SRC_ALPHA   4  
#define BLEND_FUNC_ONE_MINUS_DST_ALPHA   5    
    
/*******************************************************************************
*   Definition of contants for the command STENCIL_OP
*******************************************************************************/  
  
#define STENCIL_OP_ZERO         0    
#define STENCIL_OP_KEEP         1
#define STENCIL_OP_REPLACE      2
#define STENCIL_OP_INCR         3
#define STENCIL_OP_DECR         4
#define STENCIL_OP_INVERT       5
    
/*******************************************************************************
*   Definition of clear constants
*******************************************************************************/

#define CLEAR_TAG           0x01
#define CLEAR_STENCIL       0x02
#define CLEAR_COLOR         0x04    
    
/*******************************************************************************
*   EVE Display List Commands & related macros.
*******************************************************************************/    
    
#define DL_DISPLAY          	0x00000000  
// ---------------------------------------
#define DL_BITMAP_SOURCE    	0x01000000 
#define DLBitmapSource(address) (DL_BITMAP_SOURCE | address)    
// ---------------------------------------    
#define DL_CLEAR_COLOR_RGB    	0x02000000
#define DLClearColorRGB(red, green, blue) (DL_CLEAR_COLOR_RGB | (red << 16) | (green << 8) | blue)    
// ---------------------------------------    
#define DL_TAG             		0x03000000
#define DLTag(s) (DL_TAG | s)    
// ---------------------------------------    
#define DL_COLOR_RGB        	0x04000000 
#define DLColorRGB(red, green, blue) (DL_COLOR_RGB | (red << 16) | (green << 8) | blue)    
// ---------------------------------------    
#define DL_BITMAP_HANDLE    	0x05000000
#define DLBitmapHandle(handle) (DL_BITMAP_HANDLE | handle)    
// ---------------------------------------    
#define DL_CELL             	0x06000000
#define DLCell(cell) (DL_CELL | cell)    
// ---------------------------------------    
#define DL_BITMAP_LAYOUT    	0x07000000
#define DLBitmapLayout(format, linestride, height) (DL_BITMAP_LAYOUT | (format << 19) | (linestride << 9) | height)    
// ---------------------------------------
#define DL_BITMAP_SIZE      	0x08000000
#define DLBitmapSize(filter, wrapx, wrapy, width, height) (DL_BITMAP_SIZE | (filter << 20) | (wrapx << 19) | (wrapy << 18) | (width << 9) | height)    
// ---------------------------------------    
#define DL_ALPHA_FUNC       	0x09000000
#define DLAlphaFunc(func, ref) (DL_ALPHA_FUNC | (func << 8) | ref)    
// ---------------------------------------    
#define DL_STENCIL_FUNC     	0x0A000000
#define DLStencilFunc(func, ref, mask) (DL_STENCIL_FUNC | (func << 16) | (ref << 8) | mask)    
// ---------------------------------------    
#define DL_BLEND_FUNC       	0x0B000000
#define DLBlendFunc(src, dst) (DL_BLEND_FUNC | (src << 3) | dst)    
// ---------------------------------------    
#define DL_STENCIL_OP       	0x0C000000
#define DLStencilOp(sfail, spass) (DL_STENCIL_OP | (sfail << 3) | spass)    
// ---------------------------------------    
#define DL_POINT_SIZE       	0x0D000000
#define DLPointSize(size) (DL_POINT_SIZE | (size << 4))    
// ---------------------------------------    
#define DL_LINE_WIDTH       	0x0E000000
#define DLLineWidth(width) (DL_LINE_WIDTH | (width << 4))
// -------¡-------------------------------    
#define DL_COLOR_A          	0x10000000 
#define DLColorA(alpha) (DL_COLOR_A | alpha)
// ---------------------------------------    
#define DL_CLEAR_STENCIL    	0x11000000
#define DLClearStencil(s) (DL_CLEAR_STENCIL | s)    
// ---------------------------------------    
#define DL_CLEAR_TAG        	0x12000000
#define DLClearTag(t) (DL_CLEAR_TAG | t)    
// ---------------------------------------    
#define DL_STENCIL_MASK     	0x13000000
#define DLStencilMask(mask) (DL_STENCIL_MASK | mask)    
// ---------------------------------------    
#define DL_TAG_MASK         	0x14000000
#define DLTagMask(mask) (DL_TAG_MASK | mask)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_A   	0x15000000
#define DLBitmapTransformA(a) (DL_BITMAP_TFORM_A | a)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_B   	0x16000000
#define DLBitmapTransformB(b) (DL_BITMAP_TFORM_B | b)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_C   	0x17000000
#define DLBitmapTransformC(c) (DL_BITMAP_TFORM_C | c)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_D   	0x18000000
#define DLBitmapTransformD(d) (DL_BITMAP_TFORM_D | d)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_E   	0x19000000
#define DLBitmapTransformE(e) (DL_BITMAP_TFORM_E | e)    
// ---------------------------------------    
#define DL_BITMAP_TFORM_F   	0x1A000000
#define DLBitmapTransformF(f) (DL_BITMAP_TFORM_F | f)    
// ---------------------------------------    
#define DL_SCISSOR_XY       	0x1B000000
#define DLScissorXY(x, y) (DL_SCISSOR_XY | (x << 9) | y)    
// ---------------------------------------    
#define DL_SCISSOR_SIZE     	0x1C000000
#define DLScissorSize(width, height) (DL_SCISSOR_SIZE | (width << 10) | height)    
// ---------------------------------------    
#define DL_JUMP             	0x1E000000
#define DLJump(address) (DL_JUMP | address)    
// ---------------------------------------    
#define DL_BEGIN            	0x1F000000
#define DLBegin(primitive) (DL_BEGIN | primitive)     
// ---------------------------------------    
#define DL_CALL             	0x1D000000
#define DLCall(address) (DL_CALL | address)    
// ---------------------------------------    
#define DL_COLOR_MASK       	0x20000000
#define DLColorMask(r, g, b, a) (DL_COLOR_MASK | (r << 3) | (g << 2) | (b << 1) | a)    
// ---------------------------------------    
#define DL_END              	0x21000000
#define DLEnd() (DL_END)    
// ---------------------------------------    
#define DL_SAVE_CONTEXT     	0x22000000
#define DLSaveContext() (DL_SAVE_CONTEXT)    
// ---------------------------------------    
#define DL_RESTORE_CONTEXT  	0x23000000
#define DLRestoreContext() (DL_RESTORE_CONTEXT)    
// ---------------------------------------    
#define DL_RETURN           	0x24000000
#define DLReturn() (DL_RETURN)    
// ---------------------------------------    
#define DL_MACRO            	0x25000000
#define DLMacro(macro) (DL_MACRO | macro)    
// ---------------------------------------    
#define DL_CLEAR            	0x26000000
#define DLClear(color, stencil, tag) (DL_CLEAR | (color << 2) | (stencil << 1) | tag)    
// ---------------------------------------    
#define DL_VERTEX2F         	0x40000000
#define DLVertex2F(x, y) (DL_VERTEX2F | ((x << 4) << 15) | (y << 4))    
// ---------------------------------------    
#define DL_VERTEX2II        	0x80000000
#define DLVertex2II(x, y, handle, cell) (DL_VERTEX2II | (x << 21) | (y << 12) | (handle << 7) | cell)    

/*******************************************************************************
*   Display list function prototypes.
*******************************************************************************/ 
    
void DLStartList();
void DLListNewItem(unsigned long item);
void DLEndList();    

//**********************************************************************************    
//********************************************************************************** 
//********************************************************************************** 
//********************************************************************************** 
//********************************************************************************** 

/*******************************************************************************
*   Data types for data formating for commands.
*******************************************************************************/

typedef struct { int32 Command;} CINT32;
typedef struct { int32 Command; int8 v0; int8 v1; int8 v2; int8 v3; } CINT32_4INT8;
typedef struct { int32 Command; int32 v0; } CINT32_CINT32;
typedef struct { int32 Command; int32 v0; int32 v1; } CINT32_2CINT32;
typedef struct { int32 Command; int16 v0; int16 v1; int8 v2; int8 v3; int8 v4; int8 v5; int16 v6; int16 v7; int8 v8; int8 v9; int8 v10; int8 v11; } CINT32_2INT16_4INT8_X2;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; } CINT32_4INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int32 v4; } CINT32_4INT16_CINT32;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int32 v4; int16 v5; } CINT32_4INT16_CINT32_INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int16 v4; } CINT32_5INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int16 v4; int16 v5; } CINT32_6INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int16 v4; int16 v5; int16 v6; } CINT32_7INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int16 v4; int16 v5; int16 v6; int16 v7; } CINT32_8INT16;
typedef struct { int32 Command; int16 v0; int16 v1; int16 v2; int16 v3; int16 v4; int16 v5; int16 v6; int16 v7; int16 v8; int16 v9; } CINT32_10INT16;

/*******************************************************************************
*   Definition of constants for EVE_CoPro_EndDisplayList.
*******************************************************************************/
    
#define END_DL_NOSWAP   0    
#define END_DL_SWAP     1 

/*******************************************************************************
*   Option values for commands that use option parameter.
*******************************************************************************/

#define OPT_3D          0
#define OPT_RGB565      0
#define OPT_MONO        1
#define OPT_NODL        2
#define OPT_FLAT        256
#define OPT_SIGNED      256
#define OPT_CENTERX     512
#define OPT_CENTERY     1024
#define OPT_CENTER      1536
#define OPT_RIGHTX      2048
#define OPT_NOBACK      4096
#define OPT_NOTICKS     8192
#define OPT_NOHM        16384
#define OPT_NOPOINTER   16384
#define OPT_NOSECS      32768
#define OPT_NOHANDS     49152

/*******************************************************************************
*   EVE Coprocesor Commands & related macros.
*******************************************************************************/

#define CMD_DLSTART             0xffffff00
#define mEVE_CoPro_StartDisplayList() \
    SPI_TransferL_Write_Long(CMD_DLSTART); ramCMDOffset += 4
// ---------------------------------------
#define CMD_SWAP                0xffffff01
#define mEVE_CoPro_Swap() \
    SPI_TransferL_Write_Long(CMD_SWAP); ramCMDOffset += 4    
// ---------------------------------------    
#define CMD_INTERRUPT           0xffffff02
#define CMDInterrupt(milliseconds) \
    ((unsigned char*)&(CINT32_CINT32){CMD_INTERRUPT, milliseconds}), sizeof(CINT32_CINT32), 0
// --------------------------------------- 
#define CMD_BGCOLOR             0xffffff09
#define CMDBgcolor(red, green, blue) \
    ((unsigned char*)&(CINT32_4INT8){CMD_BGCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT8), 0
// ---------------------------------------    
#define CMD_FGCOLOR             0xffffff0a
#define CMDFgcolor(red, green, blue) \
    ((unsigned char*)&(CINT32_4INT8){CMD_FGCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT8), 0
// ---------------------------------------
#define CMD_GRADIENT            0xffffff0b
#define CMDGradient(x0, y0, red0, green0, blue0, x1, y1, red1, green1, blue1) \
    ((unsigned char*)&(CINT32_2INT16_4INT8_X2){CMD_GRADIENT, x0, y0, blue0, green0, red0, 0, x1, y1, blue1, green1, red1, 0}), sizeof(CINT32_2INT16_4INT8_X2), 0
// ---------------------------------------
#define CMD_TEXT                0xffffff0c
#define CMDTextNew(x, y, font, options, text) \
    ((unsigned char*)&(CINT32_4INT16){CMD_TEXT, x, y, font, options}), sizeof(CINT32_4INT16), (unsigned char*)text  
// ---------------------------------------
#define CMD_BUTTON              0xffffff0d
#define CMDButton(x, y, width, height, font, options, text) \
    ((unsigned char*)&(CINT32_6INT16){CMD_BUTTON, x, y, width, height, font, options}), sizeof(CINT32_6INT16), (unsigned char*)text  
// ---------------------------------------
#define CMD_KEYS                0xffffff0e
#define CMDKeys(x, y, width, height, font, options, text) \
    ((unsigned char*)&(CINT32_6INT16){CMD_KEYS, x, y, width, height, font, options}), sizeof(CINT32_6INT16), (unsigned char*)text
// ---------------------------------------
#define CMD_PROGRESS            0xffffff0f
#define CMDProgressBar(x, y, width, height, options, value, range) \
    ((unsigned char*)&(CINT32_7INT16){CMD_PROGRESS, x, y, width, height, options, value, range}), sizeof(CINT32_7INT16), 0
// ---------------------------------------
#define CMD_SLIDER              0xffffff10
#define CMDSlider(x, y, width, height, options, value, range) \
    ((unsigned char*)&(CINT32_7INT16){CMD_SLIDER, x, y, width, height, options, value, range}), sizeof(CINT32_7INT16), 0
// ---------------------------------------
#define CMD_SCROLLBAR           0xffffff11
#define CMDScrollBar(x, y, width, height, options, value, size, range) \
    ((unsigned char*)&(CINT32_8INT16){CMD_SCROLLBAR, x, y, width, height, options, value, size, range}), sizeof(CINT32_8INT16), 0
// ---------------------------------------
#define CMD_TOGGLE              0xffffff12

#define TOGGLE_STATE_OFF    0
#define TOGGLE_STATE_ON     65535

#define CMDToggle(x, y, width, font, options, state, text) \
    ((unsigned char*)&(CINT32_6INT16){CMD_TOGGLE, x, y, width, font, options, state}), sizeof(CINT32_6INT16), (unsigned char*)text
// ---------------------------------------
#define CMD_GAUGE               0xffffff13
#define CMDGauge(x, y, radius, options, major, minor, value, range) \
    ((unsigned char*)&(CINT32_8INT16){CMD_GAUGE, x, y, radius, options, major, minor, value, range}), sizeof(CINT32_8INT16), 0
// ---------------------------------------
#define CMD_CLOCK               0xffffff14
#define CMDClock(x, y, radius, options, hours, minutes, seconds, milliseconds) \
    ((unsigned char*)&(CINT32_8INT16){CMD_CLOCK, x, y, radius, options, hours, minutes, seconds, milliseconds}), sizeof(CINT32_8INT16), 0
// ---------------------------------------
#define CMD_CALIBRATE           0xffffff15
#define CMDCalibrate() ((unsigned char*)&(CINT32){CMD_CALIBRATE}), sizeof(CINT32), 0
// ---------------------------------------
#define CMD_SPINNER             0xffffff16

#define SPINNER_ROUND   0
#define SPINNER_LINEAR  1
#define SPINNER_CLOCK   2
#define SPINNER_ORBIT   3

#define CMDSpinner(x, y, style, scale) \
    ((unsigned char*)&(CINT32_4INT16){CMD_SPINNER, x, y, style, scale}), sizeof(CINT32_4INT16), 0
// ---------------------------------------
#define CMD_STOP                0xffffff17
#define CMDStop() ((unsigned char*)&(CINT32){CMD_STOP}), sizeof(CINT32), 0
// ---------------------------------------
#define CMD_MEMCRC              0xffffff18
// ---------------------------------------
#define CMD_REGREAD             0xffffff19
// ---------------------------------------
#define CMD_MEMWRITE            0xffffff1a
// ---------------------------------------
#define CMD_MEMSET              0xffffff1b
void EVE_CoPro_MemorySet(unsigned long ptr, unsigned long value, unsigned long num);
// ---------------------------------------
#define CMD_MEMZERO             0xffffff1c
#define CMDMemZero(ptr, size) \
    ((unsigned char*)&(CINT32_2CINT32){CMD_MEMZERO, ptr, size}), sizeof(CINT32_2CINT32), 0
// ---------------------------------------
#define CMD_MEMCPY              0xffffff1d
void EVE_CoPro_MemoryCopy(unsigned long source, unsigned long destiny, unsigned long num);
// ---------------------------------------
#define CMD_APPEND              0xffffff1e
#define mEVE_CoPro_Append(ptr, size) \
    EVE_CoPro_Send_UlongUlong(CMD_APPEND, ptr, size)
// ---------------------------------------
#define CMD_SNAPSHOT            0xffffff1f
#define CMDSnapshot(ptr) \
    ((unsigned char*)&(CINT32_CINT32){CMD_SNAPSHOT, ptr}), sizeof(CMD_SNAPSHOT), 0
// ---------------------------------------
#define CMD_INFLATE             0xffffff22
#define CMDInflate(ptr) \
    ((unsigned char*)&(CINT32_CINT32){CMD_INFLATE, ptr}), sizeof(CINT32_CINT32), 0
// ---------------------------------------
#define CMD_GETPTR              0xffffff23
// ---------------------------------------
#define CMD_LOADIMAGE           0xffffff24
// ---------------------------------------
#define CMD_LOADIDENTITY        0xffffff26
// ---------------------------------------
#define CMD_TRANSLATE           0xffffff27
    
// ---------------------------------------
#define CMD_SCALE               0xffffff28
#define CMDScale(x, y) \
    ((unsigned char*)&(CINT32_2CINT32){CMD_SCALE, (x * 65536), (y * 65536)}), sizeof(CINT32_2CINT32), 0
// ---------------------------------------
#define CMD_ROTATE              0xffffff29
#define CMDRotate(angle) \
    ((unsigned char*)&(CINT32_CINT32){CMD_ROTATE, ((angle * 65536) / 360)}), sizeof(CINT32_CINT32), 0
// ---------------------------------------
#define CMD_SETMATRIX           0xffffff2a
#define CMDSetmatrix() ((unsigned char*)&(CINT32){CMD_SETMATRIX}), sizeof(CINT32), 0
// ---------------------------------------
#define CMD_SETFONT             0xffffff2b
#define CMDSetfont(font, ptr) \
    ((unsigned char*)&(CINT32_2CINT32){CMD_SETFONT, font, ptr}), sizeof(CINT32_2CINT32), 0
// ---------------------------------------
#define CMD_TRACK               0xffffff2c
#define CMDTrack(x, y, width, height, tag) \
    ((unsigned char*)&(CINT32_5CINT16){CMD_TRACK, x, y, width, height, tag}), sizeof(CINT32_5CINT16), 0
// ---------------------------------------
#define CMD_DIAL                0xffffff2d
#define CMDDial(x, y, radius, options, value) \
    ((unsigned char*)&(CINT32_5INT16){CMD_DIAL, x, y, radius, options, value}), sizeof(CINT32_5INT16), 0
// ---------------------------------------
#define CMD_NUMBER              0xffffff2e
#define CMDNumber(x, y, font, options, number) \
    ((unsigned char*)&(CINT32_4INT16_CINT32){CMD_NUMBER, x, y, font, options, number}), sizeof(CINT32_4INT16_CINT32), 0
// ---------------------------------------
#define CMD_SCREENSAVER         0xffffff2f
#define CMDScreenSaver() ((unsigned char*)&(CINT32){CMD_SCREENSAVER}), sizeof(CINT32), 0
// ---------------------------------------
#define CMD_SKETCH              0xffffff30
#define CMDSketch(x, y, width, height, ptr, format) \
    ((unsigned char*)&(CINT32_4INT16_CINT32_INT16){CMD_SKETCH, x, y, width, height, ptr, format}), sizeof(CINT32_4INT16_CINT32_INT16), 0
// ---------------------------------------
#define CMD_LOGO                0xffffff31
#define CMDLogo() ((unsigned char*)&(CINT32){CMD_LOGO}), sizeof(CINT32), 0
// ---------------------------------------
#define CMD_COLDSTART           0xffffff32
#define CMDColdstart() ((unsigned char*)&(CINT32){CMD_COLDSTART}), sizeof(CINT32), 0 
// ---------------------------------------
#define CMD_GETMATRIX           0xffffff33
// ---------------------------------------
#define CMD_GRADCOLOR           0xffffff34
#define CMDGradcolor(red, green, blue) \
    ((unsigned char*)&(CINT32_4INT16){CMD_GRADCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT16), 0


/*******************************************************************************
*   Function prototypes.
*******************************************************************************/

typedef union
{
    uint8 TouchTransform_Bytes[24] ;
    uint32 TouchTransform_X[6];
} TouchCalibrationValues;

typedef enum { NONE, DISPLAY, COPROCESSOR } LISTTYPE;
    
/*******************************************************************************
*   Function prototypes.
*******************************************************************************/

/* Related to display. */
uint8 FT_Init();
void FT_Display_ON();
void FT_Display_OFF();

/* Related to touch panel. */
void FT_Touch_Enable();
void FT_Touch_Disable();
uint8 FT_Touch_Calibrate();
void FT_Touch_ReadCalibrationValues(TouchCalibrationValues* values);
void FT_Touch_WriteCalibrationValues(TouchCalibrationValues* values);

/* Related to sound. */
#ifdef USE_GPIO1_AUDIO
    void FT_AUDIO_MUTE();
    void FT_AUDIO_UNMUTE();
#endif

void FT_Sound_Volume(uint8 volume);
void FT_Sound_Play(uint8 sound, uint8 pitch);
void FT_Sound_Stop();

/* Other. */
uint8 FTIsCoproccesorReady();
//void FT_Touch_Enable();
//void FT_Touch_Disable();
//void FT_Touch_Calibrate();




    void CMDStartList();
void CMDEndList(unsigned char swap);  
void CMDListAddItem(unsigned char *tobesent, unsigned int length, unsigned char *string);
void CMDListAddDLItem(unsigned long item);





void EVE_RegisterWrite(unsigned long everegister, unsigned long data);
unsigned char EVE_RegisterRead(unsigned long everegister);
void EVE_CommandWrite(unsigned char command);
void FT_Write_ByteArray_4(const unsigned char *data, unsigned long length);













    
    
    
    
#define FT_DL_SIZE              (8*1024)            //8KB Display List buffer size
#define FT_CMD_FIFO_SIZE        (4*1024)            //4KB coprocessor Fifo size
#define FT_CMD_SIZE             (4)                 //4 byte per coprocessor command of EVE    
    
//#endif /* End PSOC_EVE_LIBRARY_H */



/* *** EVE Graphics Engine Commands **** */    










    
/* *** Commands & Registers values **** */ 


#define DECR_WRAP             7UL
#define DLSWAP_DONE           0UL
#define DLSWAP_FRAME          2UL
#define DLSWAP_LINE           1UL

#define EDGE_STRIP_R          5UL
#define EDGE_STRIP_L          6UL    
#define EDGE_STRIP_A          7UL
#define EDGE_STRIP_B          8UL





    #define INCR_WRAP             6UL
#define INT_CMDEMPTY          32UL
#define INT_CMDFLAG           64UL
#define INT_CONVCOMPLETE      128UL
#define INT_PLAYBACK          16UL
#define INT_SOUND             8UL
#define INT_SWAP              1UL
#define INT_TAG               4UL
#define INT_TOUCH             2UL

    
    
    

    
    #define L1                    1UL
#define L4                    2UL
#define L8                    3UL


#define LINEAR_SAMPLES        0UL
#define LINES                 3UL
#define LINE_STRIP            4UL
#define NEAREST               0UL


//#define OPT_NOBACK            4096UL    // 0x1000    
//#define OPT_NOTICKS           8192UL    // 0x2000
//#define OPT_NOPOINTER         16384UL   // 0x4000    
//
//
//#define OPT_CENTER            1536UL    // 0x6000
//#define OPT_CENTERX           512UL     // 0x0200
//#define OPT_CENTERY           1024UL    // 0x0400
//#define OPT_FLAT              256UL     // 0x0100
//#define OPT_MONO              1UL
//#define OPT_NOBACK            4096UL    // 0x1000
//#define OPT_NODL              2UL
//#define OPT_NOHANDS           49152UL   // 0xC168
//#define OPT_NOHM              16384UL   // 0x4000
//#define OPT_NOPOINTER         16384UL   // 0x4000
//#define OPT_NOSECS            32768UL   // 0x8000
//#define OPT_NOTICKS           8192UL    // 0x2000
//#define OPT_RIGHTX            2048UL    // 0x0800
//#define OPT_SIGNED            256UL     // 0x0100
#define PALETTED              8UL
#define PLAYCOLOR             0x00a0a080
#define FTPOINTS              2UL       // "POINTS" is a reserved word
#define RECTS                 9UL
#define REPEAT                1UL

#define RGB332                4UL
#define RGB565                7UL

#define TEXT8X8               9UL
#define TEXTVGA               10UL

#define ULAW_SAMPLES          1UL
#define ZERO                  0UL    
    
//// FT800 Chip Commands - use with cmdWrite
//#define FT800_ACTIVE					0x00			// Initializes FT800
//#define FT800_STANDBY					0x41			// Place FT800 in Standby (clk running)
//#define FT800_SLEEP						0x42			// Place FT800 in Sleep (clk off)
//#define FT800_PWRDOWN					0x50			// Place FT800 in Power Down (core off)
//#define FT800_CLKEXT					0x44			// Select external clock source
//#define FT800_CLK48M					0x62			// Select 48MHz PLL
//#define FT800_CLK36M					0x61			// Select 36MHz PLL
//#define FT800_CORERST					0x68			// Reset core - all registers default

  

// Useful Macros
#define RGB(r, g, b)          ((((r) << 16) | (g) << 8) | (b))
#define SQ(v)                 ((v) * (v))
#define MIN(x,y)              ((x) > (y) ? (y) : (x))
#define MAX(x,y)              ((x) > (y) ? (x) : (y))
#define NOTE(n, sharp)        (((n) - 'C') + ((sharp) * 128))
#define F16(s)                (((s) * 65536))
#define INVALID_TOUCH_XY      0x8000
#define ABS(x)                ((x) > (0) ? (x) : (-x))
#define CLEAR_COLOR_RGB(red,green,blue) ((2UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))
#define CLEAR(c,s,t) ((38UL<<24)|(((c)&1UL)<<2)|(((s)&1UL)<<1)|(((t)&1UL)<<0))    
#define COLOR_RGB(red,green,blue) ((4UL<<24)|(((red)&255UL)<<16)|(((green)&255UL)<<8)|(((blue)&255UL)<<0))

    
    
        
//#define FT_DL_SIZE              (8*1024)            //8KB Display List buffer size
//#define FT_CMD_FIFO_SIZE        (4*1024)            //4KB coprocessor Fifo size
//#define FT_CMD_SIZE             (4)                 //4 byte per coprocessor command of EVE   
//#define INCR_WRAP             6UL
//#define INT_CMDEMPTY          32UL
//#define INT_CMDFLAG           64UL
//#define INT_CONVCOMPLETE      128UL
//#define INT_PLAYBACK          16UL
//#define INT_SOUND             8UL
//#define INT_SWAP              1UL
//#define INT_TAG               4UL
//#define INT_TOUCH             2UL
//#define LINEAR_SAMPLES        0UL
//#define LINES                 3UL
//#define LINE_STRIP            4UL
//#define NEAREST               0UL
//#define PLAYCOLOR             0x00a0a080
//#define FTPOINTS              2UL       // "POINTS" is a reserved word
//#define RECTS                 9UL
//#define REPEAT                1UL
//#define ULAW_SAMPLES          1UL
    
    
//unsigned char EVE_Init_Display();
//void EVE_Display_ON();
//void EVE_Display_OFF();
//void EVE_Touch_Enable();
//void EVE_Touch_Disable();
//void EVE_Touch_Calibrate();
//void EVE_EnableGlobalInts();
//void EVE_DisableGlobalInts();
//void EVE_EnableTouchInt();
//void EVE_DisableTouchInt();
//unsigned char EVE_Is_Copro_Ready(unsigned int *newoffset);



unsigned int IncCMDOffset(unsigned int currentoffset, unsigned char commandsize);    
    
#endif /* End PSOCEVE_LIBRARY */    

/* [] END OF FILE */
