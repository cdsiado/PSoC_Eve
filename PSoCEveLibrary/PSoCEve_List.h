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

#if !defined(PSOC_EVE_LIST_H)
#define PSOC_EVE_LIST_H
    
#include <cytypes.h>    
    
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
*   Definition about swaping mode.
*******************************************************************************/
    
#define DLSWAP_LINE           1UL    
#define DLSWAP_FRAME          2UL    
    
    
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
*    
*   Every DL (display list) commmand is implemented as a function like macro. 
*   For a description of parameters for every command read related comments.
*   Every macro is a wrapper to a display list commands, so to know what every
*   display command does read the FT Programmers Guide from FTDI.    
*******************************************************************************/    
    
/* Macro name : DL_DISPLAY.
   Description: Wrapper to DL_DISPLAY command.
*/   
#define DL_DISPLAY          	0x00000000  

/* Macro name : DLBitmapSource
   Description: Wrapper to DL_BITMAP_SOURCE command.
   Parameters:
        address:    pointer to FT RAM_G where bitmap is stored.
*/    
#define DL_BITMAP_SOURCE    	0x01000000 
#define _DLBitmapSource(address) (DL_BITMAP_SOURCE | address)   
    
inline void DLBitmapSource(uint32 address);

/* Macro name : DLClearColorRGB
   Description: Wrapper to DL_CLEAR_COLOR_RGB command.
   Parameters:
        red: 8 bits, max = 255; green: 8 bits, max = 255; blue: 8 bits, max = 255    
*/   
#define DL_CLEAR_COLOR_RGB    	0x02000000
#define _DLClearColorRGB(red, green, blue) (DL_CLEAR_COLOR_RGB | (red << 16) | (green << 8) | blue)
    
inline void DLClearColorRGB(uint8 red, uint8 green, uint8 blue);    



/* Macro name : DLTag
   Description: Wrapper to DL_TAG command.
   Parameters:
        s: 8 bits, max = 255   
*/  
#define DL_TAG             		0x03000000
#define _DLTag(s) (DL_TAG | s)    

inline void DLTag(uint8 tag);

/* Macro name : DLColorRGB
   Description: Wrapper to DL_COLOR_RGB command.
   Parameters:
        red: 8 bits, max = 255; green: 8 bits, max = 255; blue: 8 bits, max = 255   
*/  
#define DL_COLOR_RGB        	0x04000000 
#define _DLColorRGB(red, green, blue) (DL_COLOR_RGB | (red << 16) | (green << 8) | blue)    

inline void DLColorRGB(uint8 red, uint8 green, uint8 blue);

/* Macro name : DLBitmapHandle
   Description: Wrapper to DL_BITMAP_HANDLE command.
   Parameters:
        handle: 5 bits, max = 31    
*/  
#define DL_BITMAP_HANDLE    	0x05000000
#define _DLBitmapHandle(handle) (DL_BITMAP_HANDLE | handle)  

inline void DLBitmapHandle(uint8 handle);

/* Macro name : DLCell
   Description: Wrapper to DL_CELL command.
   Parameters:
        cell: 7 bits  
*/      
#define DL_CELL             	0x06000000
#define _DLCell(cell) (DL_CELL | cell)    

inline void DLCell(uint8 cell);

/* Macro name : DLBitmapLayout
   Description: Wrapper to DL_BITMAP_LAYOUT command.
   Parameters:
        format: 5 bits, max = 11; linestride: 10 bits; height: 9 bits
*/    
#define DL_BITMAP_LAYOUT    	0x07000000
#define _DLBitmapLayout(format, linestride, height) (DL_BITMAP_LAYOUT | (format << 19) | (linestride << 9) | height)    

inline void DLBitmapLayout(uint8 format, uint16 linestride, uint16 height);

/* Macro name : DLBitmapSize
   Description: Wrapper to DL_BITMAP_SIZE command.
   Parameters:
        filter: 1 bit; wrapx: 1 bit; wrapy: 1 bit; width: 9 bits; height: 9 bits    
*/        
#define DL_BITMAP_SIZE      	0x08000000
#define _DLBitmapSize(filter, wrapx, wrapy, width, height) (DL_BITMAP_SIZE | (filter << 20) | (wrapx << 19) | (wrapy << 18) | (width << 9) | height)    

inline void DLBitmapSize(uint8 filter, uint8 wrapx, uint8 wrapy, uint16 width, uint16 height);

/* Macro name : DLAlphaFunc
   Description: Wrapper to DL_ALPHA_FUNC command.
   Parameters:
        func: 3 bits; ref: 8 bits    
*/        
#define DL_ALPHA_FUNC       	0x09000000
#define _DLAlphaFunc(func, ref) (DL_ALPHA_FUNC | (func << 8) | ref)    

inline void DLAlphaFunc(uint8 func, uint8 ref);

/* Macro name : DLStencilFunc
   Description: Wrapper to DL_STENCIL_FUNC command.
   Parameters:
        func: 4 bits; ref: 8 bits; mask: 8 bits    
*/      
#define DL_STENCIL_FUNC     	0x0A000000
#define _DLStencilFunc(func, ref, mask) (DL_STENCIL_FUNC | (func << 16) | (ref << 8) | mask) 

inline void DLStencilFunc(uint8 func, uint8 ref, uint8 mask);

/* Macro name : DLBlendFunc
   Description: Wrapper to DL_BLEND_FUNC command.
   Parameters:
        src: 3 bits; dst: 3 bits    
*/  
#define DL_BLEND_FUNC       	0x0B000000
#define _DLBlendFunc(src, dst) (DL_BLEND_FUNC | (src << 3) | dst)  

inline void DLBlendFunc(uint8 src, uint8 dst);

/* Macro name : DLStencilOp
   Description: Wrapper to DL_STENCIL_OP command.
   Parameters:
        sfail: 3 bits; spass: 3 bits    
*/      
#define DL_STENCIL_OP       	0x0C000000
#define _DLStencilOp(sfail, spass) (DL_STENCIL_OP | (sfail << 3) | spass)   

inline void DLStencilOp(uint8 sfail, uint8 spass);

/* Macro name : DLPointSize
   Description: Wrapper to DL_POINT_SIZE command.
   Parameters:
        size: 17 bits 
        Parameters are multiplied by 16.
*/  
#define DL_POINT_SIZE       	0x0D000000
#define _DLPointSize(size) (DL_POINT_SIZE | (size << 4))  

inline void DLPointSize(uint32 size);

/* Macro name : DLLineWidth
   Description: Wrapper to DL_LINE_WIDTH command.
   Parameters:
        width: 12 bits   
        Parameters are multiplied by 16.
*/  
#define DL_LINE_WIDTH       	0x0E000000
#define _DLLineWidth(width) (DL_LINE_WIDTH | (width << 4))

inline void DLLineWidth(uint16 width);

/* Macro name : DLColorAlpha
   Description: Wrapper to DL_COLOR_ALPHA (DL_COLOR_A) command.
   Parameters:
        alpha: 8 bits    
*/  
#define DL_COLOR_A          	0x10000000 
#define _DLColorA(alpha) (DL_COLOR_A | alpha)

inline void DLColorA(uint8 alpha);

/* Macro name : DLClearStencil
   Description: Wrapper to DL_CLEAR_STENCIL command.
   Parameters:
        s: 8 bits    
*/      
#define DL_CLEAR_STENCIL    	0x11000000
#define _DLClearStencil(s) (DL_CLEAR_STENCIL | s)  

inline void DLClearStencil(uint8 s);

/* Macro name : DLClearTag
   Description: Wrapper to DL_CLEAR_TAG command.
   Parameters:
        t: 8 bits    
*/      
#define DL_CLEAR_TAG        	0x12000000
#define _DLClearTag(t) (DL_CLEAR_TAG | t)    

inline void DLClearTag(uint8 t);

/* Macro name : DLStencilMask
   Description: Wrapper to DL_STENCIL_MASK command.
   Parameters:
        mask: 8 bits    
*/      
#define DL_STENCIL_MASK     	0x13000000
#define _DLStencilMask(mask) (DL_STENCIL_MASK | mask)   

inline void DLStencilMask(uint8 mask);

/* Macro name : DLTagMask
   Description: Wrapper to DL_TAG_MASK command.
   Parameters:
        mask: 1 bit    
*/      
#define DL_TAG_MASK         	0x14000000
#define _DLTagMask(mask) (DL_TAG_MASK | mask) 

inline void DLTagMask(uint8 mask);

/* Macro name : DLBitmapTransformA
   Description: Wrapper to DL_BITMAP_TFORM_A (DL_BITMAP_TRANSFORM_A) command.
   Parameters:
        a: 17 bits    
*/      
#define DL_BITMAP_TFORM_A   	0x15000000
#define _DLBitmapTransformA(a) (DL_BITMAP_TFORM_A | a)    

inline void DLBitmapTransformA(uint32 a);

/* Macro name : DLBitmapTransformB
   Description: Wrapper to DL_BITMAP_TFORM_B (DL_BITMAP_TRANSFORM_B) command.
   Parameters:
        b: 17 bits    
*/   
#define DL_BITMAP_TFORM_B   	0x16000000
#define _DLBitmapTransformB(b) (DL_BITMAP_TFORM_B | b)  

inline void DLBitmapTransformB(uint32 b);

/* Macro name : DLBitmapTransformC
   Description: Wrapper to DL_BITMAP_TFORM_C (DL_BITMAP_TRANSFORM_C) command.
   Parameters:
        c: 24 bits    
*/   
#define DL_BITMAP_TFORM_C   	0x17000000
#define _DLBitmapTransformC(c) (DL_BITMAP_TFORM_C | c)    

inline void DLBitmapTransformC(uint32 c);

/* Macro name : DLBitmapTransformD
   Description: Wrapper to DL_BITMAP_TFORM_D (DL_BITMAP_TRANSFORM_D) command.
   Parameters:
        d: 17 bits    
*/   
#define DL_BITMAP_TFORM_D   	0x18000000
#define _DLBitmapTransformD(d) (DL_BITMAP_TFORM_D | d)    

inline void DLBitmapTransformD(uint32 d);

/* Macro name : DLBitmapTransformE
   Description: Wrapper to DL_BITMAP_TFORM_E (DL_BITMAP_TRANSFORM_E) command.
   Parameters:
        e: 17 bits    
*/   
#define DL_BITMAP_TFORM_E   	0x19000000
#define _DLBitmapTransformE(e) (DL_BITMAP_TFORM_E | e) 

inline void DLBitmapTransformE(uint32 e);

/* Macro name : DLBitmapTransformF
   Description: Wrapper to DL_BITMAP_TFORM_F (DL_BITMAP_TRANSFORM_F) command.
   Parameters:
        F: 24 bits    
*/   
#define DL_BITMAP_TFORM_F   	0x1A000000
#define _DLBitmapTransformF(f) (DL_BITMAP_TFORM_F | f) 

inline void DLBitmapTransformF(uint32 f);

/* Macro name : DLScissorXY
   Description: Wrapper to DL_SCISSOR_XY command.
   Parameters:
        x: 9 bits; y: 9 bits  
*/   
#define DL_SCISSOR_XY       	0x1B000000
#define _DLScissorXY(x, y) (DL_SCISSOR_XY | (x << 9) | y) 

inline void DLScissorXY(uint16 x, uint16 y);

/* Macro name : DLScissorSize
   Description: Wrapper to DL_SCISSOR_SIZE command.
   Parameters:
        width: 10 bits; height: 10 bits  
*/   
#define DL_SCISSOR_SIZE     	0x1C000000
#define _DLScissorSize(width, height) (DL_SCISSOR_SIZE | (width << 10) | height)    

inline void DLScissorSize(uint16 width, uint16 height);

/* Macro name : DLJump
   Description: Wrapper to DL_JUMP command.
   Parameters:
        address: 16 bits  
*/   
#define DL_JUMP             	0x1E000000
#define _DLJump(address) (DL_JUMP | address)    

inline void DLJump(uint16 address);

/* Macro name : DLBegin
   Description: Wrapper to DL_BEGIN command.
   Parameters:
        primitive: 4 bits  
*/       
#define DL_BEGIN            	0x1F000000
#define _DLBegin(primitive) (DL_BEGIN | primitive)   

inline void DLBegin(uint8 primitive);

/* Macro name : DLCall
   Description: Wrapper to DL_CALL command.
   Parameters:
        address: 16 bits  
*/      
#define DL_CALL             	0x1D000000
#define _DLCall(address) (DL_CALL | address)    

inline void DLCall(uint16 address);

/* Macro name : DLColorMask
   Description: Wrapper to DL_COLOR_MASK command.
   Parameters:
        r: 1 bit; g: 1 bit; b: 1 bit; a: 1 bit    
*/      
#define DL_COLOR_MASK       	0x20000000
#define _DLColorMask(r, g, b, a) (DL_COLOR_MASK | (r << 3) | (g << 2) | (b << 1) | a)    

inline void DLColorMask(uint8 r, uint8 g, uint8 b, uint8 a);

/* Macro name : DLEND
   Description: Wrapper to DL_END command.  
*/  
#define DL_END              	0x21000000
#define _DLEnd() (DL_END)    

inline void DLEnd();

/* Macro name : DLSaveContext
   Description: Wrapper to DL_SAVE_CONTEXT command.  
*/
#define DL_SAVE_CONTEXT     	0x22000000
#define _DLSaveContext() (DL_SAVE_CONTEXT)    

inline void DLSaveContext();

/* Macro name : DLRestoreContext
   Description: Wrapper to DL_RESTORE_CONTEXT command.  
*/    
#define DL_RESTORE_CONTEXT  	0x23000000
#define _DLRestoreContext() (DL_RESTORE_CONTEXT)   

inline void DLRestoreContext();

/* Macro name : DLReturn
   Description: Wrapper to DL_RETURN command.  
*/    
#define DL_RETURN           	0x24000000
#define _DLReturn() (DL_RETURN)    

inline void DLReturn();

/* Macro name : DLMacro
   Description: Wrapper to DL_MACRO command.
   Parameters:
        macro: 1 bit  
*/      
#define DL_MACRO            	0x25000000
#define _DLMacro(macro) (DL_MACRO | macro)   

inline void DLMacro(uint8 macro);

/* Macro name : DLClear
   Description: Wrapper to DL_CLEAR command.
   Parameters:
        color: 1 bit; stencil: 1 bit; tag: 1 bit   
*/      
#define DL_CLEAR            	0x26000000
#define _DLClear(color, stencil, tag) (DL_CLEAR | (color << 2) | (stencil << 1) | tag) 

inline void DLClear(uint8 color, uint8 stencil, uint8 tag);

/* Macro name : DLVertex2F
   Description: Wrapper to DL_VERTEX2F command.
   Parameters:
        x: 15 bits; y: 15 bits
        Parameters are multiplied by 16.
*/  
#define DL_VERTEX2F         	0x40000000
#define _DLVertex2F(x, y) (DL_VERTEX2F | ((x << 4) << 15) | (y << 4))  

inline void DLVertex2F(int16 x, int16 y);

/* Macro name : DLVertex2F
   Description: Wrapper to DL_VERTEX2F command.
   Parameters:
        x: 9 bits; y: 9 bits; handle: 5 bits; cell: 7 bits
*/      
#define DL_VERTEX2II        	0x80000000
#define _DLVertex2II(x, y, handle, cell) (DL_VERTEX2II | (x << 21) | (y << 12) | (handle << 7) | cell) 

inline void DLVertex2II(uint16 x, uint16 y, uint8 handle, uint8 cell);

/*******************************************************************************
*   EVE Coproccesor List Commands & related macros.
*    
*   Every CMD (coproccesor list) commmand is implemented as a function like
*   macro. 
*   For a description of parameters for every command read related comments.
*   Every macro is a wrapper to a coproccesor list command, so to know what
*   every display command does read the FT Programmers Guide from FTDI.    
*******************************************************************************/   

/*******************************************************************************
*   Data types for data formating.
*******************************************************************************/

typedef struct { int32 Command;} CINT32;
typedef struct { int32 Command; int8 v0; int8 v1; int8 v2; int8 v3; } CINT32_4INT8;
typedef struct { int32 Command; int32 v0; } CINT32_CINT32;
typedef struct { int32 Command; int32 v0; int32 v1; } CINT32_2CINT32;
typedef struct { int32 Command; int32 v0; int32 v1; int32 v2; } CINT32_3CINT32;
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

/* Macro name : CMDDLStart
   Description: Wrapper to CMD_DLSTART command.
*/ 
#define CMD_DLSTART             0xffffff00
#define _CMDDLStart() ((uint8*)&(CINT32){CMD_DLSTART}), sizeof(CINT32), 0

inline void CMDDLStart();

/* Macro name : CMDSwap
   Description: Wrapper to CMD_Swap command.
*/ 
#define CMD_SWAP                0xffffff01
#define _CMDSwap() ((uint8*)&(CINT32){CMD_SWAP}), sizeof(CINT32), 0   

inline void CMDSwap();

/* Macro name : CMDInterrupt
   Description: Wrapper to CMD_INTERRUPT command.
   Parameters:
        milliseconds: int32;
*/ 
#define CMD_INTERRUPT           0xffffff02
#define _CMDInterrupt(milliseconds) \
    ((uint8*)&(CINT32_CINT32){CMD_INTERRUPT, milliseconds}), sizeof(CINT32_CINT32), 0

inline void CMDInterrupt(uint32 milliseconds);

/* Macro name : CMDBgcolor
   Description: Wrapper to CMD_BGCOLOR command.
   Parameters:
        red: int8; green: int8; blue: int8
*/ 
#define CMD_BGCOLOR             0xffffff09
#define _CMDBgcolor(red, green, blue) \
    ((uint8*)&(CINT32_4INT8){CMD_BGCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT8), 0

inline void CMDBgcolor(int8 red, int8 green, int8 blue);

/* Macro name : CMDFgcolor
   Description: Wrapper to CMD_FGCOLOR command.
   Parameters:
        red: int8; green: int8; blue: int8
*/ 
#define CMD_FGCOLOR             0xffffff0a
#define _CMDFgcolor(red, green, blue) \
    ((uint8*)&(CINT32_4INT8){CMD_FGCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT8), 0

inline void CMDFgcolor(int8 red, int8 green, int8 blue);

/* Macro name : CMDGradient
   Description: Wrapper to CMD_GRADIENT command.
   Parameters:
        x0: int16; y0: int16; red0: int8; green0: int8; blue0: int8
        x1: int16; y1: int16; red1: int8; green1: int8; blue1: int8 
*/ 
#define CMD_GRADIENT            0xffffff0b
#define _CMDGradient(x0, y0, red0, green0, blue0, x1, y1, red1, green1, blue1) \
    ((uint8*)&(CINT32_2INT16_4INT8_X2){CMD_GRADIENT, x0, y0, blue0, green0, red0, 0, x1, y1, blue1, green1, red1, 0}), sizeof(CINT32_2INT16_4INT8_X2), 0

inline void CMDGradient(int16 x0, int16 y0, int8 red0, int8 green0, int8 blue0, int16 x1, int16 y1, int8 red1, int8 green1, int8 blue1);

/* Macro name : CMDText
   Description: Wrapper to CMD_TEXT command.
   Parameters:
        x: int16; y: int16; font int16; options: int16; text: pointer to char array
*/ 
#define CMD_TEXT                0xffffff0c
#define _CMDTextNew(x, y, font, options, text) \
    ((uint8*)&(CINT32_4INT16){CMD_TEXT, x, y, font, options}), sizeof(CINT32_4INT16), (unsigned char*)text  

inline void CMDText(int16 x, int16 y, int16 font, int16 options, char* text);

/* Macro name : CMDButton
   Description: Wrapper to CMD_BUTTON command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; font: int16
        options: int16; text: pointer to char array
*/ 
#define CMD_BUTTON              0xffffff0d
#define _CMDButton(x, y, width, height, font, options, text) \
    ((uint8*)&(CINT32_6INT16){CMD_BUTTON, x, y, width, height, font, options}), sizeof(CINT32_6INT16), (unsigned char*)text  

inline void CMDButton(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text);

/* Macro name : CMDKeys
   Description: Wrapper to CMD_KEYS command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; font: int16
        options: int16; text: pointer to char array
*/ 
#define CMD_KEYS                0xffffff0e
#define _CMDKeys(x, y, width, height, font, options, text) \
    ((uint8*)&(CINT32_6INT16){CMD_KEYS, x, y, width, height, font, options}), sizeof(CINT32_6INT16), (unsigned char*)text

inline void CMDKeys(int16 x, int16 y, int16 width, int16 height, int16 font, int16 options, char* text);

/* Macro name : CMDProgressBar
   Description: Wrapper to CMD_PROGRESS command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; 
        options: int16; value: int16; range: int16
*/ 
#define CMD_PROGRESS            0xffffff0f
#define _CMDProgressBar(x, y, width, height, options, value, range) \
    ((uint8*)&(CINT32_7INT16){CMD_PROGRESS, x, y, width, height, options, value, range}), sizeof(CINT32_7INT16), 0

inline void CMDProgressBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range);

/* Macro name : CMDSlider
   Description: Wrapper to CMD_SLIDER command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; 
        options: int16; value: int16; range: int16
*/ 
#define CMD_SLIDER              0xffffff10
#define _CMDSlider(x, y, width, height, options, value, range) \
    ((uint8*)&(CINT32_7INT16){CMD_SLIDER, x, y, width, height, options, value, range}), sizeof(CINT32_7INT16), 0

inline void CMDSlider(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 range);

/* Macro name : CMDScrollBar
   Description: Wrapper to CMD_SCROLLBAR command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; 
        options: int16; value: int16; size: int16; range: int16
*/ 
#define CMD_SCROLLBAR           0xffffff11
#define _CMDScrollBar(x, y, width, height, options, value, size, range) \
    ((uint8*)&(CINT32_8INT16){CMD_SCROLLBAR, x, y, width, height, options, value, size, range}), sizeof(CINT32_8INT16), 0

inline void CMDScrollBar(int16 x, int16 y, int16 width, int16 height, int16 options, int16 value, int16 size, int16 range);

/* Macro name : CMDToggle
   Description: Wrapper to CMD_TOGGLE command.
   Parameters:
        x: int16; y: int16; width: int16; font: int16; 
        options: int16; state: int16; text: pointer to char array
*/ 
#define CMD_TOGGLE              0xffffff12

#define TOGGLE_STATE_OFF    0
#define TOGGLE_STATE_ON     65535

#define _CMDToggle(x, y, width, font, options, state, text) \
    ((uint8*)&(CINT32_6INT16){CMD_TOGGLE, x, y, width, font, options, state}), sizeof(CINT32_6INT16), (unsigned char*)text

inline void CMDToggle(int16 x, int16 y, int16 width, int16 font, int16 options, int16 state, char* text);
    

/* Macro name : CMDGauge
   Description: Wrapper to CMD_GAUGE command.
   Parameters:
        x: int16; y: int16; radius: int16; options: int16; 
        major: int16; minor: int16; value: int16; range: int16
*/
#define CMD_GAUGE               0xffffff13
#define _CMDGauge(x, y, radius, options, major, minor, value, range) \
    ((uint8*)&(CINT32_8INT16){CMD_GAUGE, x, y, radius, options, major, minor, value, range}), sizeof(CINT32_8INT16), 0

inline void CMDGauge(int16 x, int16 y, int16 radius, int16 options, int16 major, int16 minor, int16 value, int16 range);

/* Macro name : CMDClock
   Description: Wrapper to CMD_CLOCK command.
   Parameters:
        x: int16; y: int16; radius: int16; options: int16; 
        hours: int16; minutes: int16; seconds: int16; milliseconds: int16
*/
#define CMD_CLOCK               0xffffff14
#define _CMDClock(x, y, radius, options, hours, minutes, seconds, milliseconds) \
    ((uint8*)&(CINT32_8INT16){CMD_CLOCK, x, y, radius, options, hours, minutes, seconds, milliseconds}), sizeof(CINT32_8INT16), 0

inline void CMDClock(int16 x, int16 y, int16 radius, int16 options, int16 hours, int16 minutes, int16 seconds, int16 milliseconds);

/* Macro name : CMDCalibrate
   Description: Wrapper to CMD_CALIBRATE command.
*/
#define CMD_CALIBRATE           0xffffff15
#define _CMDCalibrate() ((uint8*)&(CINT32){CMD_CALIBRATE}), sizeof(CINT32), 0

inline void CMDCalibrate();

/* Macro name : CMDSpinner
   Description: Wrapper to CMD_SPINNER command.
   Parameters:
        x: int16; y: int16; style: int16; scale: int16
*/
#define CMD_SPINNER             0xffffff16

#define SPINNER_ROUND   0
#define SPINNER_LINEAR  1
#define SPINNER_CLOCK   2
#define SPINNER_ORBIT   3

#define _CMDSpinner(x, y, style, scale) \
    ((uint8*)&(CINT32_4INT16){CMD_SPINNER, x, y, style, scale}), sizeof(CINT32_4INT16), 0

inline void CMDSpinner(int16 x, int16 y, int16 style, int16 scale);

/* Macro name : CMDStop
   Description: Wrapper to CMD_STOP command.
*/
#define CMD_STOP                0xffffff17
#define _CMDStop() ((uint8*)&(CINT32){CMD_STOP}), sizeof(CINT32), 0

inline void CMDStop();

/*****/
#define CMD_MEMCRC              0xffffff18

/*****/
#define CMD_REGREAD             0xffffff19

/*****/
#define CMD_MEMWRITE            0xffffff1a

/* Macro name : CMDMemSet
   Description: Wrapper to CMD_MEMSET command.
   Parameters:
        ptr: int32; value: int32; size: int32
*/
#define CMD_MEMSET              0xffffff1b
#define _CMDMemSet(ptr, value, size) \
    ((uint8*)&(CINT32_3CINT32){CMD_MEMSET, ptr, value, size}), sizeof(CINT32_3CINT32), 0

inline void CMDMemSet(int32 ptr, int32 value, int32 size);

/* Macro name : CMDMemZero
   Description: Wrapper to CMD_MEMZERO command.
   Parameters:
        ptr: int32; size: int32
*/
#define CMD_MEMZERO             0xffffff1c
#define _CMDMemZero(ptr, size) \
    ((uint8*)&(CINT32_2CINT32){CMD_MEMZERO, ptr, size}), sizeof(CINT32_2CINT32), 0

inline void CMDMemZero(int32 ptr, int32 size);

/* Macro name : CMDMemCopy
   Description: Wrapper to CMD_MEMCPY command.
   Parameters:
        dest: int32; src: int32; size: int32
*/
#define CMD_MEMCPY              0xffffff1d
#define _CMDMemCopy(dest, src, size) \
    ((uint8*)&(CINT32_3CINT32){CMD_MEMCPY, dest, src, size}), sizeof(CINT32_3CINT32), 0

inline void CMDMemCopy(int32 dest, int32 src, int32 size);

/* Macro name : CMDAppend
   Description: Wrapper to CMD_APPEND command.
   Parameters:
        ptr: int32; size: int32
*/
#define CMD_APPEND              0xffffff1e
#define _CMDAppend(ptr, size) \
    ((uint8*)&(CINT32_2CINT32){CMD_APPEND, ptr, size}), sizeof(CINT32_2CINT32), 0

inline void CMDAppend(int32 ptr, int32 size);

/* Macro name : CMDSnapshot
   Description: Wrapper to CMD_SNAPSHOT command.
   Parameters:
        ptr: int32
*/
#define CMD_SNAPSHOT            0xffffff1f
#define _CMDSnapshot(ptr) \
    ((uint8*)&(CINT32_CINT32){CMD_SNAPSHOT, ptr}), sizeof(CMD_SNAPSHOT), 0

inline void CMDSnapshot(int32 ptr);

/* Macro name : CMDInflate
   Description: Wrapper to CMD_INFLATE command.
   Parameters:
        ptr: int32
*/
#define CMD_INFLATE             0xffffff22
#define _CMDInflate(ptr) \
    ((uint8*)&(CINT32_CINT32){CMD_INFLATE, ptr}), sizeof(CINT32_CINT32), 0

inline void CMDInflate(int32 ptr);

/*****/
#define CMD_GETPTR              0xffffff23

/*****/
#define CMD_LOADIMAGE           0xffffff24

/* Macro name : CMDLoadIdentity
   Description: Wrapper to CMD_LOADIDENTITY command.
*/
#define CMD_LOADIDENTITY        0xffffff26
#define _CMDLoadIdentity() ((uint8*)&(CINT32){CMD_LOADIDENTITY}), sizeof(CINT32), 0

inline void CMDLoadIdentity();

/* Macro name : CMDTranslate
   Description: Wrapper to CMD_TRANSLATE command.
   Parameters:
        tx: int32; ty: int32
        Parameters are multiplied by 65536
*/
#define CMD_TRANSLATE           0xffffff27
#define _CMDTranslate(tx, ty) \
    ((uint8*)&(CINT32_2CINT32){CMD_TRANSLATE, tx * 65536, ty * 65536}), sizeof(CINT32_2CINT32), 0

inline void CMDTranslate(int32 tx, int32 ty);
    
/* Macro name : CMDScale
   Description: Wrapper to CMD_SCALE command.
   Parameters:
        x: int32; y: int32
        Parameters are multiplied by 65536
*/
#define CMD_SCALE               0xffffff28
#define _CMDScale(x, y) \
    ((uint8*)&(CINT32_2CINT32){CMD_SCALE, (x * 65536), (y * 65536)}), sizeof(CINT32_2CINT32), 0

inline void CMDScale(int32 x, int32 y);

/* Macro name : CMDRotate
   Description: Wrapper to CMD_ROTATE command.
   Parameters:
        angle: int32
        Parameters are multiplied by 65536 and divided by 360
*/
#define CMD_ROTATE              0xffffff29
#define _CMDRotate(angle) \
    ((uint8*)&(CINT32_CINT32){CMD_ROTATE, ((angle * 65536) / 360)}), sizeof(CINT32_CINT32), 0

inline void CMDRotate(int32 angle);

/* Macro name : CMDSetmatrix
   Description: Wrapper to CMD_SETMATRIX command.
*/
#define CMD_SETMATRIX           0xffffff2a
#define _CMDSetmatrix() ((uint8*)&(CINT32){CMD_SETMATRIX}), sizeof(CINT32), 0

inline void CMDSetmatrix();

/* Macro name : CMDSetfont
   Description: Wrapper to CMD_SETFONT command.
   Parameters:
        font: int32; ptr: int32
*/
#define CMD_SETFONT             0xffffff2b
#define _CMDSetfont(font, ptr) \
    ((uint8*)&(CINT32_2CINT32){CMD_SETFONT, font, ptr}), sizeof(CINT32_2CINT32), 0

inline void CMDSetfont(int32 font, int32 ptr);

/* Macro name : CMDTrack
   Description: Wrapper to CMD_TRACK command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; tag: int16
*/
#define CMD_TRACK               0xffffff2c
#define _CMDTrack(x, y, width, height, tag) \
    ((uint8*)&(CINT32_5INT16){CMD_TRACK, x, y, width, height, tag}), sizeof(CINT32_5INT16), 0

inline void CMDTrack(int16 x, int16 y, int16 width, int16 height, int16 tag);

/* Macro name : CMDDial
   Description: Wrapper to CMD_DIAL command.
   Parameters:
        x: int16; y: int16; radius: int16; options: int16; value: int16
*/
#define CMD_DIAL                0xffffff2d
#define _CMDDial(x, y, radius, options, value) \
    ((uint8*)&(CINT32_5INT16){CMD_DIAL, x, y, radius, options, value}), sizeof(CINT32_5INT16), 0

inline void CMDDial(int16 x, int16 y, int16 radius, int16 options, int16 value);

/* Macro name : CMDNumber
   Description: Wrapper to CMD_NUMBER command.
   Parameters:
        x: int16; y: int16; font: int16; options: int16; number: int32
*/
#define CMD_NUMBER              0xffffff2e
#define _CMDNumber(x, y, font, options, number) \
    ((uint8*)&(CINT32_4INT16_CINT32){CMD_NUMBER, x, y, font, options, number}), sizeof(CINT32_4INT16_CINT32), 0

inline void CMDNumber(int16 x, int16 y, int16 font, int16 options, int32 number);

/* Macro name : CMDScreenSaver
   Description: Wrapper to CMD_SCREENSAVER command.
*/
#define CMD_SCREENSAVER         0xffffff2f
#define _CMDScreenSaver() ((uint8*)&(CINT32){CMD_SCREENSAVER}), sizeof(CINT32), 0

inline void CMDScreenSaver();

/* Macro name : CMDSketch
   Description: Wrapper to CMD_SKETCH command.
   Parameters:
        x: int16; y: int16; width: int16; height: int16; ptr: int32; format: int16
*/
#define CMD_SKETCH              0xffffff30
#define _CMDSketch(x, y, width, height, ptr, format) \
    ((uint8*)&(CINT32_4INT16_CINT32_INT16){CMD_SKETCH, x, y, width, height, ptr, format}), sizeof(CINT32_4INT16_CINT32_INT16), 0

inline void CMDSketch(int16 x, int16 y, int16 width, int16 height, int32 ptr, int16 format);

/* Macro name : CMDLogo
   Description: Wrapper to CMD_LOGO command.
*/
#define CMD_LOGO                0xffffff31
#define _CMDLogo() ((uint8*)&(CINT32){CMD_LOGO}), sizeof(CINT32), 0

inline void CMDLogo();

/* Macro name : CMDColdstart
   Description: Wrapper to CMD_COLDSTART command.
   Warning: while testing, i realized that it looks FT chip needs sometime to recover from this command
            before continuing sending lists. Don´t know how to much. Needs more testing. TODO.
*/
#define CMD_COLDSTART           0xffffff32
#define _CMDColdstart() ((uint8*)&(CINT32){CMD_COLDSTART}), sizeof(CINT32), 0 

inline void CMDColdstart();

/*****/
#define CMD_GETMATRIX           0xffffff33

/* Macro name : CMDGradcolor
   Description: Wrapper to CMD_GRADCOLOR command.
   Parameters:
        red: int16; green: int16; blue: int16
*/
#define CMD_GRADCOLOR           0xffffff34
#define _CMDGradcolor(red, green, blue) \
    ((uint8*)&(CINT32_4INT16){CMD_GRADCOLOR, blue, green, red, 0}), sizeof(CINT32_4INT16), 0

inline void CMDGradcolor(int16 red, int16 green, int16 blue);
    
/*******************************************************************************
*   Typedefs.
*******************************************************************************/

/* Typedef name : LISTTYPE.
   Description: To be used to know if there is a list in progress and wich type of
                list.
*/
typedef enum { NONE, DISPLAY, COPROCESSOR } LISTTYPE;

typedef enum { OK, UNKNOWN_LIST_TYPE, LIST_IN_PROGRESS, LIST_NOT_IN_PROGRESS } FTERROR;

/*******************************************************************************
*   Definition of constants for EVE_CoPro_EndDisplayList
*******************************************************************************/

typedef enum { END_DL_NOSWAP, END_DL_SWAP } SWAPACTION;
 

/*******************************************************************************
*   Variables.
*******************************************************************************/
    

 
/*******************************************************************************
*   Function prototypes.
*******************************************************************************/

uint8 FTIsCoproccesorReady();
void FT_Write_ByteArray_4(const uint8 *data, uint32 length);
FTERROR FT_ListStart(LISTTYPE listtype);
FTERROR FT_ListEnd(SWAPACTION swap);
    
#endif /* End PSOC_EVE_LIST_H */   

/* [] END OF FILE */
